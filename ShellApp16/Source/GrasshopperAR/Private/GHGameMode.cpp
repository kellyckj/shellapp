// Fill out your copyright notice in the Description page of Project Settings.


#include "GHGameMode.h"
#include "DDLog.h"
#include "DDHelpers.h"
#include "GHBasePlayerController.h"

#include <InputCoreTypes.h>
#include <Kismet/GameplayStatics.h>

AGHGameMode::AGHGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    PlayerControllerClass = AGHBasePlayerController::StaticClass();
    
    DLOG_DEBUG("GH GAME MODE CTOR");
}

AGHGameMode::~AGHGameMode()
{
    DLOG_DEBUG("GH GAME MODE ~DTOR");
}

APlayerController*
AGHGameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString & Options)
{
    DLOG_TRACE("SpawnPlayerController: spawn options {}", TCHAR_TO_ANSI(*Options));
    FString clientPlatform = UGameplayStatics::ParseOption(Options, TEXT("GhClientPlatform"));
    FString platform = clientPlatform;
    
    if (platform.IsEmpty())
        platform = UGameplayStatics::GetPlatformName();
    
    APlayerController *controller;
    
    if (platform.Equals(TEXT("Android")) ||
        platform.Equals(TEXT("IOS")))
    {
        controller = SpawnPlayerControllerCommon(InRemoteRole, FVector::ZeroVector, FRotator::ZeroRotator, arPlayerController);
    }
    else
    {
        controller = SpawnPlayerControllerCommon(InRemoteRole, FVector::ZeroVector, FRotator::ZeroRotator, vrPlayerController);
    }
    
    return controller;
}

UClass*
AGHGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    AGHBasePlayerController *ghPlayerController = Cast<AGHBasePlayerController>(InController);
    
    if (ghPlayerController)
    {
        DLOG_DEBUG("RETURN CONTROLLER-DEFINED PAWN {}",
                   TCHAR_TO_ANSI(*ghPlayerController->ghPawnClass->GetName()));
        
        return ghPlayerController->ghPawnClass;
    }
    else
        DLOG_ERROR("couldn't get a pawn class from player controller object");
    
    return NULL;
}

void
AGHGameMode::PreLogin(const FString & Options, const FString & Address,
                      const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage)
{
    DLOG_DEBUG("PRE LOGIN: options {} address {} unique id {} error message {}",
               TCHAR_TO_ANSI(*Options), TCHAR_TO_ANSI(*Address),
               TCHAR_TO_ANSI(*(UniqueId.GetUniqueNetId()->ToString())),
               TCHAR_TO_ANSI(*ErrorMessage));
    
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* AGHGameMode::Login(UPlayer * NewPlayer, ENetRole InRemoteRole,
                                  const FString & Portal, const FString & Options,
                                  const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage)
{
    DLOG_DEBUG("LOGIN: new player. net role {} portal {} options {} unqiue id {} error message {}",
               (int)InRemoteRole,
               TCHAR_TO_ANSI(*Portal),
               TCHAR_TO_ANSI(*Options),
               TCHAR_TO_ANSI(*(UniqueId.GetUniqueNetId()->ToString())),
               TCHAR_TO_ANSI(*ErrorMessage));
    
    APlayerController *controller = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
    
    DLOG_DEBUG("LOGIN CREATED PLAYER CONTROLLER OF CLASS {}",
               TCHAR_TO_ANSI( *(controller->StaticClass()->GetDefaultObjectName().ToString())));
    
    return controller;
}

void AGHGameMode::PostLogin(APlayerController * NewPlayer)
{
    DLOG_DEBUG("POST LOGIN PLAYER CONTROLLER {}",
               TCHAR_TO_ANSI( *(NewPlayer->StaticClass()->GetDefaultObjectName().ToString())));
    
    Super::PostLogin(NewPlayer);
}
