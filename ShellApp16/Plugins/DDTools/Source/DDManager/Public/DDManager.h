//
//  DDBase.h
//  uShellTest
//
//  Created by Peter Gusev on 2/11/20.
//  Copyright 2020 Regents of the University of California
//

#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include <CoreMinimal.h>
#include <Modules/ModuleManager.h>
#include <Engine/World.h>

#include "DDHelpers.h"

class IDDModuleManagerInterface {
public:
    virtual void registerModule(IDDModuleInterface* module) = 0;
    virtual const std::vector<IDDModuleInterface*>& getRegisteredModules() = 0;
    virtual IDDModuleInterface *getModule(FString moduleName) = 0;
    virtual UWorld *getLastWorldCreated() const = 0;
    virtual FString getBuildType() const = 0;
};

class DLLEXPORT FDDModuleManager : public IModuleInterface, public IDDModuleManagerInterface
{
public:
    static IDDModuleManagerInterface* getSharedInstance();

    void registerModule(IDDModuleInterface *module) override;
    const std::vector<IDDModuleInterface*>& getRegisteredModules() override;
    IDDModuleInterface *getModule(FString moduleName) override;
    
    FString getBuildType() const override;
    UWorld *getLastWorldCreated() const override { return lastWorldCreated_; }

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

protected:
    static void onPostWorldCreation(class UWorld *world);
    static void onPostWorldInitialization(class UWorld *world,
                                          UWorld::InitializationValues iValues);
    
    void notifyPostWorldCreation(class UWorld *world);
    void notifyPostWorldInitialization(class UWorld *world);
    
private:
    std::vector<IDDModuleInterface*> registeredModules_;
    UWorld *lastWorldCreated_;
};

