//
//  DDVase.cpp
//  uShellTest
//
//  Created by Peter Gusev on 2/11/20.
//  Copyright 2020 Regents of the University of California
//

#include "DDManager.h"
#include "DDLog.h"

#include <AssetRegistryModule.h>

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

#define LOCTEXT_NAMESPACE "FDDModuleManager"

using namespace std;

//******************************************************************************
//
static IDDModuleManagerInterface *SingletonInstance = nullptr;

IDDModuleManagerInterface* FDDModuleManager::getSharedInstance()
{
    return SingletonInstance;
}

void FDDModuleManager::onPostWorldCreation(UWorld *world)
{
    if (world)
    {
        if (!world->GetMapName().Equals(FString("Untitled_0")))
        {
            if (!((FDDModuleManager*)FDDModuleManager::getSharedInstance())->lastWorldCreated_)
            {
                DLOG_TRACE("set base world: {}", TCHAR_TO_ANSI(*world->GetMapName()));
                ((FDDModuleManager*)FDDModuleManager::getSharedInstance())->lastWorldCreated_ = world;
            }
        }
        ((FDDModuleManager*)FDDModuleManager::getSharedInstance())->notifyPostWorldCreation(world);
    }
    else
        DLOG_ERROR("the world is null");
}

void FDDModuleManager::onPostWorldInitialization(UWorld *world, UWorld::InitializationValues iValues)
{
    if (world)
    {
//        DLOG_TRACE("map name: {}", TCHAR_TO_ANSI(*world->GetMapName()));
//        ((FDDModuleManager*)FDDModuleManager::getSharedInstance())->lastWorldCreated_ = world;
        ((FDDModuleManager*)FDDModuleManager::getSharedInstance())->notifyPostWorldInitialization(world);
    }
    else
        DLOG_ERROR("the world is null");
}

void FDDModuleManager::registerModule(IDDModuleInterface *module)
{
    if (module)
    {
        if (find(registeredModules_.begin(),registeredModules_.end(), module) == registeredModules_.end())
        {
            registeredModules_.push_back(module);
            DLOG_DEBUG("Successfully registered module {}",
                       TCHAR_TO_ANSI(*module->getModuleName()));
        }
        else
            DLOG_WARN("Module {} is already registered",
                      TCHAR_TO_ANSI(*module->getModuleName()));
    }
    else
        DLOG_ERROR("Bad module provided: can't register NULL module");
}

const std::vector<IDDModuleInterface*>& FDDModuleManager::getRegisteredModules()
{
    return registeredModules_;
}

IDDModuleInterface* FDDModuleManager::getModule(FString moduleName)
{
    for (auto ddModule : registeredModules_)
    {
        if (ddModule->getModuleName().Equals(moduleName))
            return ddModule;
    }
    
    return nullptr;
}

FString FDDModuleManager::getBuildType() const
{
    return FString(BUILD_TYPE_FULL(BUILD_TYPE));
}

void FDDModuleManager::StartupModule()
{
//    DLOG_DEBUG("DD Module Manager Startup");

    checkf(!SingletonInstance, TEXT("DD Module Manager singleton is already initialized"));
    SingletonInstance = this;
    
    FWorldDelegates::OnPostWorldCreation.AddStatic( &FDDModuleManager::onPostWorldCreation);
    FWorldDelegates::OnPostWorldInitialization.AddStatic(&onPostWorldInitialization);
}

void FDDModuleManager::ShutdownModule()
{
    DLOG_DEBUG("DD Module Manager Shutdown");
}

void FDDModuleManager::notifyPostWorldCreation(UWorld *world)
{
    //DLOG_DEBUG("notify {} modules", registeredModules_.size());
    
    for (auto ddModule : registeredModules_)
        ddModule->onPostWorldCreation(world);
}

void FDDModuleManager::notifyPostWorldInitialization(UWorld *world)
{
    //DLOG_DEBUG("notify {} modules", registeredModules_.size());
    
    for (auto ddModule : registeredModules_)
        ddModule->onPostWorldInitialization(world);
}

//******************************************************************************

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDDModuleManager, DDManager)
