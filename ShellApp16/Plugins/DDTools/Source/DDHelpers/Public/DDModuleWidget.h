// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DDHelpers.h"
#include "DDModuleWidget.generated.h"

/**
 *
 */
UCLASS()
class DDHELPERS_API UDDModuleWidget : public UUserWidget
{
public:
    UFUNCTION(BlueprintCallable, Category = "DD Module Widget")
    FName getModuleName();

    UFUNCTION(BlueprintCallable, Category = "DD Module Widget")
    FName getModuleVersion();
    
    UFUNCTION(BlueprintCallable, Category = "DD Module Widget")
    FName getBuildType();
    
    UFUNCTION(BlueprintCallable, Category = "DD Module Widget")
    FName getModuleNetworkMode();
    
    void setModule(IDDModuleInterface *module);

protected:
    const IDDModuleInterface *module_;

	GENERATED_BODY()

};
