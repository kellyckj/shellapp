// Fill out your copyright notice in the Description page of Project Settings.


#include "GHBasePlayerController.h"
#include "DDLog.h"

AGHBasePlayerController::AGHBasePlayerController()
: APlayerController()
{
    DLOG_DEBUG("BASE PLAYER CONTROLLER DEFAULT CTOR");
    bReplicates = true;
}

AGHBasePlayerController::AGHBasePlayerController(const FObjectInitializer& ObjectInitializer)
: APlayerController(ObjectInitializer)
{
    DLOG_DEBUG("BASE PLAYER CONTROLLER CTOR");
}

AGHBasePlayerController::~AGHBasePlayerController()
{
    DLOG_DEBUG("PLAYER CONTROLLER DTOR AGHBasePlayerController::~AGHBasePlayerController()");
}

AGHPlayerState* AGHBasePlayerController::getPlayerState()
{
    return Cast<AGHPlayerState>(GetPawn()->GetPlayerState());
}
