// Fill out your copyright notice in the Description page of Project Settings.
#include "PlaybackCtrlComponent.h"
#include "PlaybackCtrl.h"

UPlaybackCtrlComponent::UPlaybackCtrlComponent()
    : listener_(this)
{
    DLOG_TRACE("Start PlaybackCtrlComponent");
    SetIsReplicated(true);

}

UPlaybackCtrlComponent::UPlaybackCtrlComponent(FVTableHelper & helper)
    : listener_(this)
{
    // Does not need to be a valid object.
    DLOG_TRACE("Start PlaybackCtrlComponent helper");
    SetIsReplicated(true);
}


void UPlaybackCtrlComponent::OnRegister()
{
    DLOG_TRACE("Start OnRegister");
    UE_LOG(LogTemp, Log, TEXT("Start OnRegister Playbackctrl"));
    Super::OnRegister();
    FPlaybackCtrlModule* mod = FPlaybackCtrlModule::GetSharedInstance();
    if (mod)
    {
        mod->RegisterReceiver(&listener_);
        UE_LOG(LogTemp, Log, TEXT("got mod"));
        DLOG_TRACE("got mod!");
    }
    else
        UE_LOG(LogTemp, Log, TEXT("no module"));
    
}

void UPlaybackCtrlComponent::OnUnregister()
{
    FPlaybackCtrlModule* mod = FPlaybackCtrlModule::GetSharedInstance();
    if (mod)
        mod->UnregisterReceiver(&listener_);
    else
        DLOG_TRACE("no module");
    Super::OnUnregister();
}

void UPlaybackCtrlComponent::InvokeOnCueRxReplicated_Implementation(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp)
{
    UE_LOG(LogTemp, Log, TEXT("I am invoked"));
    DLOG_INFO("I am invoked");
    if (GetNetMode() == NM_Standalone)
    {
//        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I'm a standalone in replicated func!"));
        UE_LOG(LogTemp, Log, TEXT("I'm a standalone in replicated func!"));
    }
    else if (GetNetMode() == NM_ListenServer)
    {
//        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I'm a Listen Server in replicated func!"));
        UE_LOG(LogTemp, Log, TEXT("I'm a Listen Server in replicated func!"));
    }
    else if (GetNetMode() == NM_Client)
        UE_LOG(LogTemp, Log, TEXT("I'm a client!"));
    
    DLOG_TRACE(GetNetMode());
    OnCueReceived.Broadcast(Address, Data, SenderIp);
}


