// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DDModuleWidget.h"
#include "blueprintHelpers.generated.h"

/**
 * 
 */
UCLASS()
class GRASSHOPPERAR_API UblueprintHelpers : public UBlueprintFunctionLibrary
{
public:
    
    /**
     * Iterates over all Plugins folders and looks for a blueprint called "BP_InfoPanel" under
     * subpath: Content/UI.
     * @return Dictionary, where key is the plugin name and value is the path for BP_InfoPanel found,
     * or empty string if plugin does not support InfoPanel UI.
     */
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Plugins Widgets"), Category = "Master UI")
    static TArray<UDDModuleWidget*> createPluginWidgets(UUserWidget *parentWidget);
    
    UFUNCTION(BlueprintCallable, meta = (DisplayNAme = "Is AR Capable Device"), Category = "Grasshopper Helpers")
    static bool isArCapableDevice();
    
	GENERATED_BODY()
	
};
