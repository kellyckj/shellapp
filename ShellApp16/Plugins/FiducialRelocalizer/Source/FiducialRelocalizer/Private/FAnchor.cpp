// Fill out your copyright notice in the Description page of Project Settings.


#include "FAnchor.h"
#include "DDLog.h"
#include "FiducialRelocalizer.h"

// Sets default values
AFAnchor::AFAnchor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFAnchor::BeginPlay()
{
	Super::BeginPlay();
    
    DLOG_MODULE_DEBUG(FiducialRelocalizer, "FAnchor {} begin play", TCHAR_TO_ANSI(*FiducialName));
    Tags.Add(FName(*FiducialName));
}

// Called every frame
void AFAnchor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

