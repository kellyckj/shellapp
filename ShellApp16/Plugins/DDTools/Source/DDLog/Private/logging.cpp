//
// logging.cpp
//
//  Created by Peter Gusev on 12 November 2019.
//  Copyright 2013-2020 Regents of the University of California
//
#include "logging.hpp"

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <Kismet/KismetSystemLibrary.h>
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include <Misc/Paths.h>

#if PLATFORM_ANDROID
#include <android/log.h>
#endif

#if PLATFORM_IOS
#include "IOSAppDelegate.h"
#import <UIKit/UIKit.h>
#endif

using namespace std;
using namespace ddlog;

DEFINE_LOG_CATEGORY(LogDd);
#define DEFAULT_FORMAT "%E.%f [%12n] [%^%-8l%$] [thread %t] %!() : %v"

// logging level
// could be either:
// - "trace"
// - "debug"
// - "info"
// - "warn"
// - "err"
// - "critical"
#define LOG_LEVEL_ENV "DDLOG_LOG_LEVEL"
#define LOG_FORMAT_ENV "DDLOG_LOG_FMT"
#define LOG_FILE_ENV "DDLOG_LOG_FILE"

shared_ptr<spdlog::logger> mainLogger;
string logFile = "";
string logLevel = "";
once_flag onceFlag;

void initMainLogger();
void initLogger(shared_ptr<helpers::logger>);
string getDefaultLoggerName();

// init logging upon library loading
struct _LibInitializer {
    _LibInitializer() {
#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
        call_once(onceFlag, bind(initMainLogger));
#endif
    }
} libInitializer = {};

//******************************************************************************
// callback sink implementation
// @see https://github.com/gabime/spdlog/wiki/4.-Sinks#implementing-your-own-sink
#include <spdlog/sinks/base_sink.h>

template<typename Mutex>
class CallbackSink : public spdlog::sinks::base_sink <Mutex>
{

public:
    CallbackSink(helpers::LogCallback logCallback) :
    logCallback_(logCallback)
    {}

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override
    {
        fmt::basic_memory_buffer<char, 250> formatted;
        spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);

        pair<helpers::log_level,string> p(msg.level, fmt::to_string(formatted));
        msgs_.push_back(p);
    }

    void flush_() override
    {
        if (msgs_.size())
        {
            for (auto m:msgs_)
                logCallback_(m.second, m.first);
            msgs_.clear();
        }
    }

private:
    helpers::LogCallback logCallback_;
    vector<pair<helpers::log_level, string>> msgs_;
};

#include <spdlog/details/null_mutex.h>
#include <mutex>
using CallbackSinkMt = CallbackSink<mutex>;
using CallbackSinkSt = CallbackSink<spdlog::details::null_mutex>;

//******************************************************************************
namespace ddlog
{

shared_ptr<spdlog::logger> createFileLogger(string loggerName, string logFile)
{
#if PLATFORM_ANDROID || PLATFORM_IOS
    static vector<spdlog::sink_ptr> sinks;
    static once_flag flag1;
    call_once(flag1, [&](){
        auto rotateFileSink = make_shared<spdlog::sinks::rotating_file_sink_mt>(logFile,
                                                                                10*1024*1024, 3);
        sinks.push_back(rotateFileSink);
    });

    auto logger = make_shared<spdlog::logger>(loggerName, sinks.begin(), sinks.end());
    spdlog::register_logger(logger);
    return logger;
#else
    return spdlog::basic_logger_mt<spdlog::async_factory>(loggerName, logFile);
#endif
}

void newLogger(string loggerName)
{
#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
//    DLOG_TRACE("creating module logger {}", loggerName);
    shared_ptr<spdlog::logger> logger;

    if (logFile != "")
        logger = createFileLogger(loggerName, logFile);
    else
        logger = spdlog::stdout_color_mt(loggerName);

    initLogger(logger);
//    DLOG_TRACE("logger {} created", loggerName);
#endif
}

shared_ptr<spdlog::logger> getMainLogger()
{
    return spdlog::get(getDefaultLoggerName());
}

shared_ptr<spdlog::logger> getLogger(string loggerName)
{
    auto logger = spdlog::get(loggerName);
    return logger;
}

void flushLogger(string loggerName)
{
    if (spdlog::get(loggerName))
        spdlog::get(loggerName)->flush();
}

void registerCallback(shared_ptr<helpers::logger> logger, helpers::LogCallback callback)
{
    logger->sinks().push_back(make_shared<CallbackSinkMt>(callback));
}

}

string getDefaultLoggerName() {
   return TCHAR_TO_UTF8(*UKismetSystemLibrary::GetGameName());
}

string getDefaultLogFile()
{
    string gameName(TCHAR_TO_UTF8(*UKismetSystemLibrary::GetGameName()));
    // TODO: make this platform-specific
#if PLATFORM_ANDROID
    char cmdLine[512];
    FILE *f = fopen("/proc/self/cmdline", "r");
    if (f)
    {
        size_t c = fread(cmdLine, 512, 1, f);
    }
    else
        UE_LOG(LogTemp, Log, TEXT("FAILED TO READ /proc/self/cmdline"));

    return "/data/data/"+string(cmdLine)+"/"+gameName+".log";
#elif PLATFORM_IOS
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    return string([documentsDirectory UTF8String])+"/"+gameName+".log";
#elif PLATFORM_WINDOWS
    // temporary fix for windows.
    // check back here for possible fix https://udn.unrealengine.com/questions/563432/view.html
    FString path = FString("."); //FPaths::ProjectUserDir();
    #if WITH_EDITOR
        return string(TCHAR_TO_ANSI(*path)) + "/" + gameName + "-Editor.log";
    #else
        return string(TCHAR_TO_ANSI(*path)) + "/" + gameName + ".log";
    #endif
#else
    #if WITH_EDITOR
        return "/tmp/"+gameName+"-Editor.log";
    #else
        return "/tmp/"+gameName+".log";
    #endif
#endif
}

void initMainLogger()
{
    logLevel = getenv(LOG_LEVEL_ENV) ? string(getenv(LOG_LEVEL_ENV)) : "";
    logFile = getenv(LOG_FILE_ENV) ? string(getenv(LOG_FILE_ENV)) : getDefaultLogFile();

    if (logFile != "")
        mainLogger = createFileLogger(getDefaultLoggerName(), logFile);
    else
        mainLogger = spdlog::stdout_color_mt(getDefaultLoggerName());

    spdlog::flush_every(chrono::seconds(1));
    spdlog::set_default_logger(mainLogger);
    spdlog::set_pattern(getenv(LOG_FORMAT_ENV) ? getenv(LOG_FORMAT_ENV) : DEFAULT_FORMAT);
    initLogger(mainLogger);
}

void initLogger(shared_ptr<helpers::logger> logger)
{
    logger->flush_on(spdlog::level::err);
    if (logLevel == "")
#ifdef UE_BUILD_DEBUG
        logLevel = "trace";
        logger->flush_on(spdlog::level::debug);
#else
        logLevel = "info";
        logger->flush_on(spdlog::level::warn);
#endif

    logger->set_level(spdlog::level::from_str(logLevel));
    logger->info("Initialized logger {}: level {} file {}",  logger->name(),
        spdlog::level::to_short_c_str(logger->level()), logFile);
    logger->flush();

#if 0
    // register UE_LOG sink by default
    registerCallback(logger, [](const string& msg, const helpers::log_level& lvl){
        FString fMsg(msg.c_str());

        switch (lvl) {
            case helpers::log_level::warn:
                UE_LOG(LogShell, Warning, TEXT("DDLog: %s"), *fMsg);
                break;
            case helpers::log_level::err:
                UE_LOG(LogShell, Error, TEXT("DDLog: %s"), *fMsg);
                break;
            case helpers::log_level::info:
                UE_LOG(LogShell, Display, TEXT("DDLog: %s"), *fMsg);
                break;
            case helpers::log_level::debug:
                UE_LOG(LogShell, Log, TEXT("DDLog: %s"), *fMsg);
                break;
            case helpers::log_level::trace: // fall through
            default:
                UE_LOG(LogShell, Verbose, TEXT("DDLog: %s"), *fMsg);
                break;
        }
    });
#endif

    // register onscreen rendering sink
    registerCallback(logger, [logger](const string& msg, const helpers::log_level& lvl){

        if (!GEngine) return;

        FString fMsg(msg.c_str());

        switch (lvl) {
            case helpers::log_level::warn:
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, fMsg);
                break;
            case helpers::log_level::err:
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, fMsg);
                break;
            case helpers::log_level::info:
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, fMsg);
                break;
            case helpers::log_level::debug:
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, fMsg);
                break;
            case helpers::log_level::trace: // fall through
            default:
                GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Cyan, fMsg);
                break;
        }
    });

#if PLATFORM_ANDROID
    // register android log sink
    registerCallback(logger, [logger](const string& msg, const helpers::log_level& lvl){
        switch (lvl) {
            case helpers::log_level::warn:
                __android_log_print(ANDROID_LOG_WARN, logger->name().c_str(), "%s", msg.c_str());
                break;
            case helpers::log_level::err:
                __android_log_print(ANDROID_LOG_ERROR, logger->name().c_str(), "%s", msg.c_str());
                break;
            case helpers::log_level::info:
                __android_log_print(ANDROID_LOG_INFO, logger->name().c_str(), "%s", msg.c_str());
                break;
            case helpers::log_level::debug:
                __android_log_print(ANDROID_LOG_DEBUG, logger->name().c_str(), "%s", msg.c_str());
                break;
            case helpers::log_level::trace: // fall through
            default:
                __android_log_print(ANDROID_LOG_VERBOSE, logger->name().c_str(), "%s", msg.c_str());
                break;
        }
    });
#endif
}
