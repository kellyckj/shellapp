// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FAnchor.generated.h"

UCLASS()
class FIDUCIALRELOCALIZER_API AFAnchor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFAnchor();

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
    FString FiducialName;
    
    // specified which levels to stream in when this fiducial is detected
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
    TArray<FName> StreamingLevels;
    
    // specifies whether all other currently loaded levels must be unloaded first
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
    bool IsExclusive;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
