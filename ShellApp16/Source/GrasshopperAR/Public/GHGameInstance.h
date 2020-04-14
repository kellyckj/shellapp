// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GHGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GRASSHOPPERAR_API UGHGameInstance : public UGameInstance
{
public:
    UGHGameInstance();
    UGHGameInstance(const FObjectInitializer& ObjectInitializer);
    ~UGHGameInstance();
    
    UFUNCTION(BlueprintCallable)
    FString getCodeVersion() const;
    
    UFUNCTION(BlueprintCallable)
    FString getBranchName() const;
    
	GENERATED_BODY()
	
};
