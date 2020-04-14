// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GHGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GRASSHOPPERAR_API AGHGameMode : public AGameModeBase
{
    ~AGHGameMode();
    
//	GENERATED_BODY()
    GENERATED_UCLASS_BODY()
	
    UPROPERTY(EditAnywhere)
    TSubclassOf<APlayerController> vrPlayerController;
    
    UPROPERTY(EditAnywhere)
    TSubclassOf<APlayerController> arPlayerController;
    
    APlayerController *SpawnPlayerController(ENetRole InRemoteRole, const FString & Options) override;
    UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
    
    virtual void PreLogin(const FString & Options, const FString & Address,
                  const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage) override;
    
    virtual APlayerController * Login(UPlayer * NewPlayer, ENetRole InRemoteRole,
                                      const FString & Portal, const FString & Options,
                                      const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage) override;
    
    virtual void PostLogin(APlayerController * NewPlayer) override;
};
