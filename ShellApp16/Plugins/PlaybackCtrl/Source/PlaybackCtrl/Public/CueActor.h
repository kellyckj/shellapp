


// *****
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaybackCtrlInterface.h"
#include "Common/OscDataElemStruct.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "CueActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FComponentCueRxSignature, const FName &, Address, const TArray<FOscDataElemStruct> &, Data, const FString &, SenderIp);


UCLASS(ClassGroup=PlaybackCtrl)
class PLAYBACKCTRL_API ACueActor : public AActor
{
    GENERATED_BODY()
    
public:
    UPROPERTY(EditAnywhere, Category=PlaybackCtrl)
    FString DepartmentFilter;
    
    UPROPERTY(EditAnywhere, Category=PlaybackCtrl)
    FString BuildFilter;
    

//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Enum)
//    EActionEnum ActionEnum;
    
    /** Add your fade in sequence here, if applicable */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlaybackCtrl)
    ULevelSequence* FadeInSeq;
    
    /** Add your run sequence here, if applicable */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlaybackCtrl)
    ULevelSequence* RunSeq;
    
    /** Add your fade out sequence here, if applicable */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlaybackCtrl)
    ULevelSequence* FadeOutSeq;
    
    UPROPERTY(BlueprintAssignable, Category=PlaybackCrtl)
    FComponentCueRxSignature OnCueRx;
    
    UPROPERTY(EditAnywhere, Category=PlaybackCtrl)
    ULevelSequencePlayer* SequencePlayer;

    
    // EVENTS
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=PlaybackCtrl)
    void OnFadeInStart(float t);
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=PlaybackCtrl)
    void OnFadeInEnd();
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=PlaybackCtrl)
    void OnRunStart(float t);
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=PlaybackCtrl)
    void OnRunEnd();
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=PlaybackCtrl)
    void OnFadeOutStart(float t);
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=PlaybackCtrl)
    void OnFadeOutEnd();
    
    TMap<FString, FString> DataDict_;
    

public:
    // Sets default values for this actor's properties
    ACueActor();
    
    /// Hot reload constructor
    ACueActor(FVTableHelper & helper);
    
    const FString & GetDepartmentFilter() const
    {
        return DepartmentFilter;
    }
    
    const FString & GetBuildFilter() const
    {
        return BuildFilter;
    }
    
    ULevelSequence* & GetFadeInSeq()
    {
        return FadeInSeq;
    }
    
    ULevelSequence* & GetRunSeq()
    {
        return RunSeq;
    }
    
    ULevelSequence* & GetFadeOutSeq()
    {
        return FadeOutSeq;
    }
    
    void SendEvent(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp)
    {
        OnCueRx.Broadcast(Address, Data, SenderIp);
    }
    
    UFUNCTION()
    void OnCueReceived(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp);
    
    void CueStateStart(ULevelSequence* Seq, FString CueStateLength, FName EndCueState);
    
    
    
protected:
    void BeginDestroy() override;

private:
    BasicCueReceiver<ACueActor> _listener;
};

