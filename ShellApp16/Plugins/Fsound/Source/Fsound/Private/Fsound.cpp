//
// Fsound.cpp
//
//  Generated on February 26 2020
//  Template created by Peter Gusev on 27 January 2020.
//  Copyright 2013-2019 Regents of the University of California
//

#include "Fsound.h"
#include "logging.hpp"
#include "git-describe.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


// FMOD related headers
#include "FMODBlueprintStatics.h"
#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_common.h"


#define STRINGIZE_VERSION(v) STRINGIZE_TOKEN(v)
#define STRINGIZE_TOKEN(t) #t
#define PLUGIN_VERSION STRINGIZE_VERSION(GIT_DESCRIBE)

#define MODULE_NAME "Fsound"
#define LOCTEXT_NAMESPACE "FFsoundModule"

void FFsoundModule::StartupModule()
{
    initModule(MODULE_NAME, PLUGIN_VERSION);

    // To log using ReLog plugin, use these macro definitions:
    // DLOG_PLUGIN_ERROR("Error message");
    // DLOG_PLUGIN_WARN("Warning message");
    // DLOG_PLUGIN_INFO("Info message");
    // DLOG_PLUGIN_DEBUG("Debug message");
    // DLOG_PLUGIN_TRACE("Trace message");

    if (IFMODStudioModule::IsAvailable())
    {
        FMOD::Studio::System* StudioSystem = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);
        if (StudioSystem)
        {
            // Use it here
            // FFMODEventInstance InstanceWrapper = UFMODBlueprintStatics::PlayEventAtLocation(ThisActor, MyEvent, FTransform(MyLocation), true);
            // FMOD::Studio::EventInstance* Instance = InstanceWrapper.Instance;
            // // Call into FMOD API directly
            // Instance->setVolume(0.5f);
            FMOD::Studio::Bank* masterBank = NULL;
            StudioSystem->loadBankFile("Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);

            FMOD::Studio::Bank* stringBank = NULL;
            StudioSystem->loadBankFile("Master Bank.string.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringBank);

            FMOD::Studio::EventDescription* testDescription = NULL;
            FMOD::Studio::EventInstance* testInstance = NULL;
            StudioSystem->getEvent("event:/Test", &testDescription);
            testDescription->createInstance(&testInstance);
            // FMOD_Studio_EventDescription_CreateInstance(TestDescription, &testInstance);
            testInstance->setVolume(0.5f);
            testInstance->start();
            // FMOD_Studio_EventInstance_Start(testInstance);
        }
    }


    // void *extraDriverData = NULL;
    // Common_Init(&extraDriverData);

    // FMOD::Studio::System* system = NULL;
    // FMOD::Studio::System::create(&system);

    // The example Studio project is authored for 5.1 sound, so set up the system output mode to match
    // FMOD::System* lowLevelSystem = NULL;
    // system->getLowLevelSystem(&lowLevelSystem);
    // lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);

    // system->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);
    
    // FMOD::Studio::Bank* masterBank = NULL;
    // system->loadBankFile(Common_MediaPath("Master Bank.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);
    
    // FMOD::Studio::Bank* stringsBank = NULL;
    // system->loadBankFile(Common_MediaPath("Master Bank.strings.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);


    // UFMODBlueprintStatics::PlayEvent2D(GetWorld(), TestEvent, true);

    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FFsoundModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFsoundModule, Fsound)
