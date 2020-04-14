//
// PlaybackCtrl.cpp
//
//  Generated on February 19 2020
//  Template created by Peter Gusev on 27 January 2020.
//  Copyright 2013-2019 Regents of the University of California
//

#include "PlaybackCtrl.h"
#include "logging.hpp"
#include "git-describe.h"
#include <mutex>

#define STRINGIZE_VERSION(v) STRINGIZE_TOKEN(v)
#define STRINGIZE_TOKEN(t) #t
#define PLUGIN_VERSION STRINGIZE_VERSION(GIT_DESCRIBE)

#define MODULE_NAME "PlaybackCtrl"
#define LOCTEXT_NAMESPACE "FPlaybackCtrlModule"

#include "OscReceiverInterface.h"
#include "PlaybackCtrlInterface.h"
#include "OscDispatcher.h"

using namespace std;
using namespace std::placeholders;

typedef function<void(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp)> OnOscMessage;
static FPlaybackCtrlModule* SharedInstance;

class OscListener {
public:
    OscListener(OnOscMessage onOscMessage) :
        listener_(this),
        onOscMessage_(onOscMessage)
    {
        // register with OSC dispatcher here
        auto oscDispatcher = UOscDispatcher::Get();
        oscDispatcher->RegisterReceiver(&listener_);
    }
    
    const FString & GetAddressFilter() const
    {
        return addressFilter_;
    }

    void SendEvent(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp)
    {
        onOscMessage_(Address, Data, SenderIp);
    }
    
private:
    FString addressFilter_;
    BasicOscReceiver<OscListener> listener_;
    OnOscMessage onOscMessage_;
};

void FPlaybackCtrlModule::StartupModule()
{
    initModule(MODULE_NAME, PLUGIN_VERSION);
    SharedInstance = this;
    // To log using ReLog plugin, use these macro definitions:
//     DLOG_PLUGIN_ERROR("Error message");
//     DLOG_PLUGIN_WARN("Warning message");
//     DLOG_PLUGIN_INFO("Info message");
//     DLOG_PLUGIN_DEBUG("Debug message");
//     DLOG_PLUGIN_TRACE("Trace message");

    // making sure OSC module is loaded
    FName oscModuleName(TEXT("OSC"));
    FModuleManager &manager = FModuleManager::Get();
    FModuleStatus oscModuleStatus;
    // force load DDManager module
    IModuleInterface *moduleIface = manager.LoadModule(oscModuleName);
    TMap<FString, FString> test;
}

void FPlaybackCtrlModule::ShutdownModule()
{
    if (listener_)
        delete listener_;
}


void FPlaybackCtrlModule::onOscReceived(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp)
{
    DLOG_PLUGIN_DEBUG("OSC RECEIVED IN PLAYBACK CTRL MODULE");
    
    // Parse OSC message
    // Current naming: /<project>/<build>/<dept>/<cue name>/<action>
    FString oscAddress = Address.ToString();
    TArray<FString> addressParts;
    
    oscAddress.ParseIntoArray(addressParts, TEXT("/"), true);
    if (addressParts.IsValidIndex(0))
    {
        if (addressParts[0] != TEXT("HighCastle") || addressParts.Num() < 5)
        {
            DLOG_PLUGIN_DEBUG("Message doesn't meet address naming requirements.");
        }
        else
        {
            for(auto receiver : _receivers)
            {
                receiver->SendEvent(Address, Data, SenderIp);
            }
        }
    }
    else
        DLOG_PLUGIN_DEBUG("Message address is incorrect.");

}

void FPlaybackCtrlModule::onPostWorldInitialization (UWorld *world)
{
    static once_flag flag;
    call_once(flag, [&](){
        oscDispatcherRegister(world);
    });
}


// added for components to register
void FPlaybackCtrlModule::RegisterReceiver(IPlaybackCtrlInterface * receiver)
{
    FScopeLock ScopeLock(&_receiversMutex);
    _receivers.AddUnique(receiver);
    UE_LOG(LogTemp, Log, TEXT("added receiver in OnRegister"));

}

void FPlaybackCtrlModule::UnregisterReceiver(IPlaybackCtrlInterface * receiver)
{
    FScopeLock ScopeLock(&_receiversMutex);
    _receivers.Remove(receiver);
}

FPlaybackCtrlModule* FPlaybackCtrlModule::GetSharedInstance()
{
    return SharedInstance;
}

void FPlaybackCtrlModule::oscDispatcherRegister(UWorld* world)
{
    DLOG_PLUGIN_DEBUG("world init plugin debug");
    
    FName oscModuleName(TEXT("OSC"));
    FModuleManager &manager = FModuleManager::Get();
    FModuleStatus oscModuleStatus;
    // force load DDManager module
    IModuleInterface *moduleIface = manager.LoadModule(oscModuleName);
    ENetMode netMode = world->GetNetMode();
    DLOG_PLUGIN_DEBUG(netMode);
    if (netMode == NM_ListenServer || netMode == NM_DedicatedServer || netMode==NM_Standalone)
    {
        if (manager.QueryModule(oscModuleName, oscModuleStatus))
        {
            bool isLoaded = oscModuleStatus.bIsLoaded;

            if (!isLoaded)
                isLoaded = (nullptr != manager.LoadModule(oscModuleName));
            if (isLoaded)
            {
                if (UOscDispatcher::Get())
                {
                    listener_ = new OscListener(bind(&FPlaybackCtrlModule::onOscReceived, this, _1, _2, _3));
                }

                else
                    DLOG_PLUGIN_ERROR("OSC dispatcher is NULL");
                }
            else
                DLOG_PLUGIN_ERROR("OSC Module could not be loaded.");
            }
        else
            DLOG_PLUGIN_ERROR("OSC Module could not be found.");
    }
    else
        DLOG_PLUGIN_ERROR("THIS IS NOT A LISTEN OR DEDICATED SERVER");
    
    if (netMode == NM_Client)
    {
        if (listener_)
            delete listener_;
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPlaybackCtrlModule, PlaybackCtrl)
