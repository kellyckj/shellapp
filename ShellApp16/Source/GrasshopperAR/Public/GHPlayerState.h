// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GHPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GRASSHOPPERAR_API AGHPlayerState : public APlayerState
{
    AGHPlayerState();
    AGHPlayerState(const FObjectInitializer& ObjectInitializer);
    ~AGHPlayerState();
    
	GENERATED_BODY()
	
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_IsAvatarHidden)
    bool isAvatarHidden;
    
    UFUNCTION(BlueprintCallable)
    void SetIsAvatarHidden(bool isHidden);
    
    UFUNCTION(BlueprintNativeEvent)
    void OnRepNotify_IsAvatarHidden();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_IsGameActive)
    bool isGameActive;
    
    UFUNCTION(BlueprintCallable)
    void SetIsGameActive(bool isActive);
    
    UFUNCTION(BlueprintNativeEvent)
    void OnRepNotify_IsGameActive();

private:

    UFUNCTION()
    void OnRep_IsAvatarHidden();
    
    UFUNCTION()
    void OnRep_IsGameActive();
};
