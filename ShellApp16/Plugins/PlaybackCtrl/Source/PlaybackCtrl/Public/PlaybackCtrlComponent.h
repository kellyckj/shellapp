// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlaybackCtrlInterface.h"
#include "OscDataElemStruct.h"

#include "PlaybackCtrlComponent.generated.h"

// declare the OnOscReceived event type

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FComponentOscReceivedSignature, const TMap<FString, FString> &, AddressDict, const TMap<FString, FString> &, DataDict, const FString &, SenderIp);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FComponentCueReceivedSignature, const FName &, Address, const TArray<FOscDataElemStruct> &, Data, const FString &, SenderIp);

UCLASS( ClassGroup=PlaybackCtrl, meta=(BlueprintSpawnableComponent) )
class PLAYBACKCTRL_API UPlaybackCtrlComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category=PlaybackCtrl)
    FString DepartmentFilter;
    
    UPROPERTY(EditAnywhere, Category=PlaybackCtrl)
    FString BuildFilter;

    UPROPERTY(BlueprintAssignable, Category=PlaybackCrtl)
    FComponentCueReceivedSignature OnCueReceived;
    
    

public:

    UPlaybackCtrlComponent();
    

    /// Hot reload constructor
    UPlaybackCtrlComponent(FVTableHelper &helper);
    
    const FString & GetDepartmentFilter() const
    {
        return DepartmentFilter;
    }

    const FString & GetBuildFilter() const
       {
           return BuildFilter;
       }
    
     void SendEvent(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp)
    {
        InvokeOnCueRxReplicated(Address, Data, SenderIp);
        // Parse OSC message
        // Current naming: /<project>/<build>/<dept>/<cue name>/<action>
//        FString oscAddress = Address.ToString();
//        TArray<FString> addressParts;
//        
//        oscAddress.ParseIntoArray(addressParts, TEXT("/"), true);
//        if (addressParts.IsValidIndex(0))
//        {
//            if (addressParts[0] != TEXT("HighCastle") || addressParts.Num() < 5)
//            {
//                DLOG_PLUGIN_DEBUG("Message doesn't meet address naming requirements.");
//            }
//        }
//        else
//            DLOG_PLUGIN_DEBUG("Message address is empty.");
//        
//       
//        TMap<FString, FString> AddressDict;
//        AddressDict.Add("Build", oscAddress[1]);
//        AddressDict.Add("Department", oscAddress[2]);
//        for (int32 Index = 3; Index < oscAddress.Num() -1; ++Index)
//        {
//            AddressDict.Add("CueName_" + Index.ToString(), oscAddress[Index]);
//        }
//        AddressDict.Add("Action", oscAddress.Last());
        
    }
    
    UFUNCTION( NetMulticast, Reliable )
    void InvokeOnCueRxReplicated(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp);


private:
    void OnRegister() override;

    void OnUnregister() override;
   

private:
    BasicCueReceiver<UPlaybackCtrlComponent> listener_;
};
