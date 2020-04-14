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

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "DDHelpers.h"
#include "DDModuleWidget.h"
#include "DDLog.h"

class DLLEXPORT FDDBaseModule : public IDDModuleInterface, public FDDLogModule
{
public:
    virtual FString getModuleName() const override;
    virtual FString getModuleVersion() const override;
    virtual FString getBuildType() const override;
    virtual FString getNetworkMode() const override;
    virtual TSubclassOf<UUserWidget> getWidgetBlueprint() const override;

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

protected:
    std::string moduleName_, pluginVersion_;
    TSubclassOf<UUserWidget> infoPanelBp_;

    void initModule(std::string moduleName, std::string pluginVersion);
    
    virtual void onPostWorldCreation(class UWorld* world) override;
    virtual void onPostWorldInitialization(class UWorld* world) override;

private:
    void initWidgetPanel();
    void registerModule();
};
