//
//  DDVase.cpp
//  uShellTest
//
//  Created by Peter Gusev on 2/11/20.
//  Copyright 2020 Regents of the University of California
//

#include "DDBase.h"
#include "DDManager.h"

#include <AssetRegistryModule.h>
#include <ARFilter.h>
#include <UObject/Class.h>
#include <UObject/UObjectIterator.h>
#include <Engine/World.h>
#include <Runtime/UMG/Public/Blueprint/UserWidget.h>
#include <Modules/ModuleManager.h>

#if WITH_EDITOR
#include "KismetEditorUtilities.h"
#endif

#define LOCTEXT_NAMESPACE "FDDBaseModule"

#define BUILD_TYPE_FULL(BuildType)(BuildType "")
#define BUILD_TYPE "Unknown"

#if WITH_EDITOR
    #undef BUILD_TYPE_FULL
    #define BUILD_TYPE_FULL(BuildType)(BuildType " Editor")
#endif

#if UE_BUILD_DEBUG
    #undef BUILD_TYPE
    #define BUILD_TYPE "Debug"
#elif UE_BUILD_DEVELOPMENT
    #undef BUILD_TYPE
    #define BUILD_TYPE "Development"
#elif UE_BUILD_TEST
    #undef BUILD_TYPE
    #define BUILD_TYPE "Test"
#elif UE_BUILD_SHIPPING
    #undef BUILD_TYPE
    #define BUILD_TYPE "Shipping"
#endif

#define NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? "Unknown" \
: (GEngine->GetNetMode(GetWorld()) == NM_Client) ? "Client" \
: (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? "ListenServer" \
: (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? "DedicatedServer" \
: "Standalone")

using namespace std;

//******************************************************************************
//
void FDDBaseModule::StartupModule()
{
    DLOG_DEBUG("Module Startup");
}

void FDDBaseModule::ShutdownModule()
{
    DLOG_DEBUG("Module Shutdown");
}

FString FDDBaseModule::getModuleName() const
{
    return FString(moduleName_.c_str());
}

FString FDDBaseModule::getModuleVersion() const
{
    return FString(pluginVersion_.c_str());
}

FString FDDBaseModule::getBuildType() const
{
    return FString(BUILD_TYPE_FULL(BUILD_TYPE));
}

FString FDDBaseModule::getNetworkMode() const
{
    // TODO: Fix NETMODE_WORLD (GetWorld() call) for non-actor class...
    return FString("TBD"); //NETMODE_WORLD);
}

TSubclassOf<UUserWidget> FDDBaseModule::getWidgetBlueprint() const
{
    return infoPanelBp_;
}

void FDDBaseModule::initModule(string moduleName, string pluginVersion)
{
    moduleName_ = moduleName;
    pluginVersion_ = pluginVersion;
    initLogger(moduleName_);

    DLOG_PLUGIN_INFO("{} module initialized. Version {}. Build Type {}. Network mode {}",
                     moduleName,
                     TCHAR_TO_ANSI(*getModuleVersion()),
                     TCHAR_TO_ANSI(*getBuildType()),
                     TCHAR_TO_ANSI(*getNetworkMode()));

    initWidgetPanel();
    registerModule();
}

void FDDBaseModule::initWidgetPanel()
{
    string packagePath = "/"+moduleName_;
    TArray<TAssetSubclassOf<UObject>> widgets;
    ddhelpers::GetAllBlueprintSubclasses(widgets,
                                        FName("DDModuleWidget"),
                                        false,
                                        FString(packagePath.c_str()));

    if (widgets.Num())
    {
        infoPanelBp_ = widgets[0].Get();
        DLOG_PLUGIN_DEBUG("plugin panel {}", TCHAR_TO_ANSI(*widgets[0].GetAssetName()));
    }
    else
    {
        DLOG_PLUGIN_WARN("No default widgets found");
        infoPanelBp_ = nullptr;
    }
}

void FDDBaseModule::registerModule()
{
    FName ddModuleManagerName(TEXT("DDManager"));
    FModuleManager &manager = FModuleManager::Get();
    FModuleStatus ddManagerModuleStatus;
    // force load DDManager module
    IModuleInterface *moduleIface = manager.LoadModule(ddModuleManagerName);
    
    if (manager.QueryModule(ddModuleManagerName, ddManagerModuleStatus))
    {
        bool isLoaded = ddManagerModuleStatus.bIsLoaded;
        
        if (!isLoaded)
            isLoaded = (nullptr != manager.LoadModule(ddModuleManagerName));
            
        if (isLoaded)
        {
            IDDModuleManagerInterface *ddManager = FDDModuleManager::getSharedInstance();
            
            ddManager->registerModule(this);
        }
        else
            DLOG_PLUGIN_ERROR("DD Module Manager could not be loaded. Module registration failed");
    }
    else
        DLOG_PLUGIN_ERROR("DD Module Manager could not be found. Module registration failed");
    
}

void FDDBaseModule::onPostWorldCreation(UWorld *world)
{
//    DLOG_PLUGIN_TRACE("map {} created. callback unused: override for catching world creation",
//                      TCHAR_TO_ANSI(*world->GetMapName()));
}

void FDDBaseModule::onPostWorldInitialization(UWorld *world)
{
//    DLOG_PLUGIN_TRACE("map {} initialized. callback unused: override for catching world initialization",
//                      TCHAR_TO_ANSI(*world->GetMapName()));
}

//******************************************************************************

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDDBaseModule, DDBase)
