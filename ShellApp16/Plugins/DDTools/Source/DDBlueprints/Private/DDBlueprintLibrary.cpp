// Fill out your copyright notice in the Description page of Project Settings.


#include "DDBlueprintLibrary.h"
#include "DDLog.h"
#include "DDManager.h"

using namespace std;

void UDDBlueprintLibrary::LogInfo(FString fText)
{
    string text(TCHAR_TO_UTF8(*fText));
    DLOG_INFO(text);
}

void UDDBlueprintLibrary::LogWarning(FString fText)
{
    string text(TCHAR_TO_UTF8(*fText));
    DLOG_WARN(text);
}

void UDDBlueprintLibrary::LogError(FString fText)
{
    string text(TCHAR_TO_UTF8(*fText));
    DLOG_ERROR(text);
}

void UDDBlueprintLibrary::LogDebug(FString fText)
{
    string text(TCHAR_TO_UTF8(*fText));
    DLOG_DEBUG(text);
}

void UDDBlueprintLibrary::LogTrace(FString fText)
{
    string text(TCHAR_TO_UTF8(*fText));
    DLOG_TRACE(text);
}

FString UDDBlueprintLibrary::getGameNetMode()
{
    UWorld *world = FDDModuleManager::getSharedInstance()->getLastWorldCreated();
    
    if (world)
    {
        ENetMode mode = world->GetNetMode();
        
        switch (mode) {
            case NM_Standalone:
                return FString("NM_Standalone");
            case NM_DedicatedServer:
                return FString("NM_DedicatedServer");
            case NM_ListenServer:
                return FString("NM_ListenServer");
            case NM_Client:
                return FString("NM_Client");
            default:
                break;
                
        }
    }
    
    return FString("Unknown");
}

FString UDDBlueprintLibrary::getBuildType()
{
    return FDDModuleManager::getSharedInstance()->getBuildType();
}

FString UDDBlueprintLibrary::getLoggingLevel()
{
    return FString(spdlog::level::to_short_c_str(ddlog::getMainLogger()->level()));
}

FString UDDBlueprintLibrary::getServerIp()
{
    UWorld *world = FDDModuleManager::getSharedInstance()->getLastWorldCreated();
     
     if (world)
     {
         ENetMode mode = world->GetNetMode();
         
         switch (mode) {
             case NM_Standalone:
                 return FString();
             default:
                 return world->URL.Host;
         }
     }
    
    return FString();
}

int UDDBlueprintLibrary::getServerPort()
{
    UWorld *world = FDDModuleManager::getSharedInstance()->getLastWorldCreated();
     
     if (world)
         return world ->URL.Port;
    
    return 0;
}
