// Fill out your copyright notice in the Description page of Project Settings.


#include "CueActor.h"
#include "PlaybackCtrl.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlayer.h"

// Sets default values
ACueActor::ACueActor()
    : _listener(this)
{
    FPlaybackCtrlModule* mod = FPlaybackCtrlModule::GetSharedInstance();
    if (mod)
    {
        mod->RegisterReceiver(&_listener);
        UE_LOG(LogTemp, Log, TEXT("got mod"));
        DLOG_TRACE("got mod!");
    }
    else
        UE_LOG(LogTemp, Log, TEXT("no module"));
    
    OnCueRx.AddDynamic(this, &ACueActor::OnCueReceived);

}

ACueActor::ACueActor(FVTableHelper & helper)
    : _listener(this)
{
    
}
// Called when the game starts or when spawned
void ACueActor::BeginDestroy()
{
    FPlaybackCtrlModule* mod = FPlaybackCtrlModule::GetSharedInstance();
    if (mod)
        mod->UnregisterReceiver(&_listener);
    else
        DLOG_TRACE("no module");

    Super::BeginDestroy();
}

void ACueActor::OnCueReceived(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp)
{
    // Parse OSC message
    // Address: Current naming: /<project>/<build>/<dept>/<cue name>/<action>
    FString oscAddress = Address.ToString();
    TArray<FString> addressParts;
    oscAddress.ParseIntoArray(addressParts, TEXT("/"), true);
    TMap<FString, FString> AddressDict;

    AddressDict.Add(TEXT("Build"), addressParts[1]);
    AddressDict.Add(TEXT("Department"), addressParts[2]);
    AddressDict.Add(TEXT("CueName"), addressParts[3]);
//    for (int32 Index = 3; Index < addressParts.Num() -1; ++Index)
//    {
//        AddressDict.Add(TEXT("CueName_") + FString::FromInt(Index), addressParts[Index]);
//    }
    AddressDict.Add(TEXT("Action"), addressParts.Last());

    // Arguments
    TMap<FString, FString> DataDict;
    TArray<FString> d;
    for (auto& elem : Data)
    {
        elem.AsStringValue().ToString().ParseIntoArray(d, TEXT("="), true);
        DataDict.Add(d[0], d[1]);
    }
    DataDict_ = DataDict;
    // Handle pausing/resuming
    FString theAction = AddressDict["Action"].ToLower();
    if (AddressDict["CueName"] == GetHumanReadableName())
    {
        if (SequencePlayer)
        {
            if (theAction == "pause")
                SequencePlayer->Pause();
            else if (theAction == "resume")
                SequencePlayer->Play();
        }
        else if (theAction == "go")
            OnFadeInStart(0);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("This cue isn't for %s"), *GetHumanReadableName());
    }
}

void ACueActor::OnFadeInStart_Implementation(float t)
{
    if (GetFadeInSeq())
        CueStateStart(GetFadeInSeq(), "FadeInLength", "OnFadeInEnd");
    else
        OnFadeInEnd();
}

void ACueActor::OnFadeInEnd_Implementation()
{
     // Add any fade in end implementation code here-- could be empty
    SequencePlayer = nullptr;
    OnRunStart(0);
    
}


void ACueActor::OnRunStart_Implementation(float t)
{
    if (GetRunSeq())
        CueStateStart(GetRunSeq(), "RunLength","OnRunEnd");
    else
        OnRunEnd();
}

void ACueActor::OnRunEnd_Implementation()
{
     // Add any run end implementation code here-- could be empty
    SequencePlayer = nullptr;
    OnFadeOutStart(0);
}

void ACueActor::OnFadeOutStart_Implementation(float t)
{
    if (GetFadeOutSeq())
        CueStateStart(GetFadeOutSeq(), "FadeOutLength","OnFadeOutEnd");
    else
        OnFadeOutEnd();
}

void ACueActor::OnFadeOutEnd_Implementation()
{
     // Add any fade out end implementation code here-- could be empty
}

void ACueActor::CueStateStart(ULevelSequence* Seq, FString CueStateLength, FName EndCueState)
{
    if (SequencePlayer == nullptr)
    {
        ALevelSequenceActor* LevelSequenceActor;
        SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Seq, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);
        if (DataDict_.Contains(CueStateLength))
        {
            float l = FCString::Atof(*DataDict_[CueStateLength]);
            float d = SequencePlayer->GetDuration().AsSeconds();
            SequencePlayer->SetPlayRate(d/l);
        }
    }
            
    if (SequencePlayer)
    {
        FScriptDelegate funcDelegate;
        funcDelegate.BindUFunction(this, EndCueState);
        SequencePlayer->OnFinished.AddUnique(funcDelegate);
        SequencePlayer->PlayToFrame(0);
        SequencePlayer->Play();
    }
}
