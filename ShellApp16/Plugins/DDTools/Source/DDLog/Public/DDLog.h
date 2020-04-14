//
// ReLog.h
//
//  Generated on January 27 2020
//  Template created by Peter Gusev on 27 January 2020.
//  Copyright 2013-2020 Regents of the University of California
//

// A Boilerplate code for a C++/BP plugin that handles third-party dependencies automatically.
// How to use:
// 1. Give a name to your plugin replacing placeholder <#Your Module Name#>
// 2. Rename all plugin files and folders according your plugin's name:
//      Boilerplate.h, Boilerplate.cpp, Boilerplate.Build.cs, Boilerplate.uplugin
// 3. Fix #include "Boilerplate.h" in .cpp file
//
// To add third-party dependencies:
// 1. Place your third-party folder (that has header files and binaries) in the "deps" subfolder.
// 2. Your third-party dependencies must have this folder structure:
//      <third-party lib name>
//          *- include      // headers should be placed here
//          *- lib          // (optional, can skip for header-only dependencies)
//              *- Android  // include only those platforms, that your third-party supports
//              *- IOS
//              *- macOS
//              *- Win64

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "logging.hpp"

#define DLOG_MODULE_TRACE(mname, ...) DLOG_LOGGER_TRACE(ddlog::getLogger(#mname), ##__VA_ARGS__)
#define DLOG_MODULE_DEBUG(mname, ...) DLOG_LOGGER_DEBUG(ddlog::getLogger(#mname), ##__VA_ARGS__)
#define DLOG_MODULE_INFO(mname, ...) DLOG_LOGGER_INFO(ddlog::getLogger(#mname), ##__VA_ARGS__)
#define DLOG_MODULE_WARN(mname, ...) DLOG_LOGGER_WARN(ddlog::getLogger(#mname), ##__VA_ARGS__)
#define DLOG_MODULE_ERROR(mname, ...) DLOG_LOGGER_ERROR(ddlog::getLogger(#mname), ##__VA_ARGS__)

#define DLOG_PLUGIN_TRACE(...) DLOG_LOGGER_TRACE(logger_, ##__VA_ARGS__)
#define DLOG_PLUGIN_DEBUG(...) DLOG_LOGGER_DEBUG(logger_, ##__VA_ARGS__)
#define DLOG_PLUGIN_INFO(...) DLOG_LOGGER_INFO(logger_, ##__VA_ARGS__)
#define DLOG_PLUGIN_WARN(...) DLOG_LOGGER_WARN(logger_, ##__VA_ARGS__)
#define DLOG_PLUGIN_ERROR(...) DLOG_LOGGER_ERROR(logger_, ##__VA_ARGS__)

class UDDModuleWidget;

class DLLEXPORT FDDLogModule : public IModuleInterface
{
public:

    FDDLogModule();
    virtual ~FDDLogModule();

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
    std::shared_ptr<ddlog::helpers::logger> logger_;

    void initLogger(std::string loggerName);
};
