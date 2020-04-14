// Fill out your copyright notice in the Description page of Project Settings.


#include "GHGameInstance.h"
#include "DDLog.h"
#include "git-describe.h"

#define STRINGIZE_VERSION(v) STRINGIZE_TOKEN(v)
#define STRINGIZE_TOKEN(t) #t
#define CODE_VERSION STRINGIZE_VERSION(GIT_DESCRIBE)
#define BRANCH_NAME STRINGIZE_VERSION(GIT_BRANCH)

UGHGameInstance::UGHGameInstance()
:UGameInstance()
{
    DLOG_DEBUG("GAME INSTANCE DEFAULT CTOR");
}

UGHGameInstance::UGHGameInstance(const FObjectInitializer& ObjectInitializer)
:UGameInstance(ObjectInitializer)
{
    DLOG_DEBUG("GAME INSTANCE CTOR");
}

UGHGameInstance::~UGHGameInstance()
{
    DLOG_DEBUG("GAME INSTANCE DTOR");
}

FString
UGHGameInstance::getCodeVersion() const
{
    return FString(CODE_VERSION);
}

FString
UGHGameInstance::getBranchName() const
{
    return FString(BRANCH_NAME);
}
