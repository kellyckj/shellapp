// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDHelpers.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "DDBlueprintLibrary.generated.h"

/**
 *
 */
UCLASS()
class DDBLUEPRINTS_API UDDBlueprintLibrary : public UBlueprintFunctionLibrary
{
public:
    UFUNCTION(BlueprintCallable, Category = "DDLog")
    static void LogInfo(FString text);

    UFUNCTION(BlueprintCallable, Category = "DDLog")
    static void LogWarning(FString text);

    UFUNCTION(BlueprintCallable, Category = "DDLog")
    static void LogError(FString text);

    UFUNCTION(BlueprintCallable, Category = "DDLog")
    static void LogDebug(FString text);

    UFUNCTION(BlueprintCallable, Category = "DDLog")
    static void LogTrace(FString text);
    
    UFUNCTION(BlueprintCallable, Category = "DDManager")
    static FString getGameNetMode();
    
    UFUNCTION(BlueprintCallable, Category = "DDManager")
    static FString getBuildType();
    
    UFUNCTION(BlueprintCallable, Category = "DDManager")
    static FString getLoggingLevel();
    
    // returns server IP address if NetMode is Client or Server (dedicated or listen)
    // returns empty string in Standalone
    UFUNCTION(BlueprintCallable, Category = "DDManager")
    static FString getServerIp();
    
    // ???
    UFUNCTION(BlueprintCallable, Category = "DDManager")
    static int getServerPort();
    
	GENERATED_BODY()

};
