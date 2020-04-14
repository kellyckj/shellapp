//
// logging.hpp
//
//  Created by Peter Gusev on 27 January 2020.
//  Copyright 2013-2020 Regents of the University of California
//

#ifndef __logging_hpp__
#define __logging_hpp__

// to disable logging,
// set SPDLOG_ACTIVE_LEVEL to SPDLOG_LEVEL_OFF below
#ifdef UE_BUILD_DEBUG
    // #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
    DECLARE_LOG_CATEGORY_EXTERN(LogDd, VeryVerbose, All);
#else
    // #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
    DECLARE_LOG_CATEGORY_EXTERN(LogDd, Log, All);
#endif

#include "Core.h"

// disable exceptions
#define SPDLOG_NO_EXCEPTIONS
#include <spdlog/spdlog.h>

#define DLOG_TRACE SPDLOG_TRACE
#define DLOG_DEBUG SPDLOG_DEBUG
#define DLOG_INFO SPDLOG_INFO
#define DLOG_WARN SPDLOG_WARN
#define DLOG_ERROR SPDLOG_ERROR

#define DLOG_LOGGER_TRACE SPDLOG_LOGGER_TRACE
#define DLOG_LOGGER_DEBUG SPDLOG_LOGGER_DEBUG
#define DLOG_LOGGER_INFO SPDLOG_LOGGER_INFO
#define DLOG_LOGGER_WARN SPDLOG_LOGGER_WARN
#define DLOG_LOGGER_ERROR SPDLOG_LOGGER_ERROR
#define DLOG_LOGGER_CRITICAL SPDLOG_LOGGER_CRITICAL

#define DLOG_TRACE_TAG(tag, ...) (DLOG_TRACE(tag##__VA_ARGS__))

namespace ddlog {
    namespace helpers {
        typedef spdlog::logger logger;
        typedef spdlog::level::level_enum log_level;
        typedef std::function<void(const std::string&, const log_level&)> LogCallback;
    }

    DLLEXPORT void newLogger(std::string loggerName);
    DLLEXPORT std::shared_ptr<helpers::logger> getMainLogger();
    DLLEXPORT std::shared_ptr<helpers::logger> getLogger(std::string loggerName);
    DLLEXPORT void flushLogger(std::string loggerName);
    DLLEXPORT void registerCallback(std::shared_ptr<helpers::logger>, helpers::LogCallback);
}

#endif
