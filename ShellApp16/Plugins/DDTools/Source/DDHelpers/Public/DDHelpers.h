//
//  uHelpers.h
//  uShellTest
//
//  Created by Peter Gusev on 2/11/20.
//  Copyright 2020 Regents of the University of California
//

#pragma once

#include <stdio.h>
#include "Object.h"
#include "ScriptMacros.h"
#include "Blueprint/UserWidget.h"
#include <UObject/Class.h>
#include <UObject/UObjectIterator.h>

// common interface for DD modules
class IDDModuleInterface
{
public:
    virtual FString getModuleName() const = 0;
    virtual FString getModuleVersion() const = 0;
    virtual FString getBuildType() const = 0;
    virtual FString getNetworkMode() const = 0;
    virtual TSubclassOf<UUserWidget> getWidgetBlueprint() const = 0;
    virtual void onPostWorldCreation(class UWorld* world) = 0;
    virtual void onPostWorldInitialization(class UWorld* world) = 0;
};

class FDDHelpersModule : public IModuleInterface
{
};

// adapted from https://github.com/kamrann/KantanCodeExamples/blob/master/Source/A1_GatherSubclasses/Runtime/A1_GatherSubclasses.h
namespace ddhelpers
{
namespace Detail
{
#if 0
        // causes link error
        //
        // Undefined symbols for architecture x86_64:
        //  "FKismetEditorUtilities::IsClassABlueprintSkeleton(UClass const*)", referenced from:
        //          ddhelpers::Detail::GetAllNativeSubclasses(TArray<TSoftClassPtr<UObject>, TSizedDefaultAllocator<32> >&, TSubclassOf<UObject>, bool) in Module.DDHelpers.cpp.o
        // ld: symbol(s) not found for architecture x86_64
        //
        // adding "Kismet" module as a dependency does not help
        DLLEXPORT void GetAllNativeSubclasses(TArray<TAssetSubclassOf<UObject>>& OutSubclasses,
                                              TSubclassOf<UObject> Base, bool bAllowAbstract);
#endif
        DLLEXPORT void GetAllBlueprintSubclasses(TArray<TAssetSubclassOf<UObject>>& OutSubclasses,
                                                 FName BaseClassName/*TSubclassOf< UObject > Base*/,
                                                 bool bAllowAbstract, FString const& Path);
}

#if 0
    template < typename TBase >
    void DLLEXPORT GetAllNativeSubclasses(TArray<TAssetSubclassOf<UObject>>& Subclasses,
                                          TSubclassOf<TBase> Base, bool bAllowAbstract)
    {
        TArray<TAssetSubclassOf<UObject>> Classes;
        Detail::GetAllNativeSubclasses(Classes, Base, bAllowAbstract);
        for(auto & Cls : Classes)
        {
            Subclasses.Add(Cls);
        }
    }
#endif

    void DLLEXPORT GetAllBlueprintSubclasses(TArray<TAssetSubclassOf<UObject>>& Subclasses,
                                             FName BaseClassName /*TSubclassOf< TBase > Base*/,
                                             bool bAllowAbstract, FString const& Path);
}
