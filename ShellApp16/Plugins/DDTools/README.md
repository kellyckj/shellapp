# DDTools
Developer tools UE4 plugin.
Contains following modules:

* `DDLog` -- logging based on [spdlog](https://github.com/gabime/spdlog)
* `DDBase` -- base class to derive user modules from
* `DDHelpers` -- define interfaces and plugin widget base class
* `DDManager` -- manager for plugins, derived from DDBase
* `DDBlueprints` -- blueprint function library

## Description

### DDLog

`DDLog` is a custom logging module, based on [spdlog](https://github.com/gabime/spdlog).

> ❓ *Cool! But... why?*
> As the project gets more complex, due to multiplatform support, it is important to have helpful tools for filtering out log output during development and testing. `DDLog` is designed to fan out log output to multiple destinations, such as files, network sinks, device consoles, on-screen rednering, etc. If using `DDBase` as a base class for your modules, the logging will appear pre-formatted and can be easily filtered based on the pluginn name.

#### Hot to use

By default, there's an app-wide logger, named after game name. Use these macro to log:

```
DLOG_ERROR("Error log line with argument1 {} and argument two {}", 42, "string_argument");
DLOG_WARN("Warning log line with argument1 {} and argument two {}", 42, "string_argument");
DLOG_INFO("Info log line with argument1 {} and argument two {}", 42, "string_argument");
DLOG_DEBUG("Debug log line with argument1 {} and argument two {}", 42, "string_argument");
DLOG_TRACE("Trace log line with argument1 {} and argument two {}", 42, "string_argument");
```

**Logging FString**

```
DLOG_INFO("Here comes FString: {}", TCHAR_TO_ANSI(*fstringVar));
```

**Logging FName**

```
DLOG_INFO("Here comes FName: {}", TCHAR_TO_ANSI(*fnameVar.ToString()));
```

**Logging levels**

Logging levels at runtime are controled with environment variable `DDLOG_LOG_LEVEL` which can take these values:
* *"trace"*
* *"debbug"*
* *"info"*
* *"warn"*
* *"err"*

**DBase module logging**

If your module is derived form `DDBase`, you shall use these macro for module-level logging:
```
DLOG_PLUGIN_ERROR
DLOG_PLUGIN_WARN
DLOG_PLUGIN_INFO
DLOG_PLUGIN_DEBUG
DLOG_PLUGIN_TRACE
```
See more on the `DDbase` [below](#DDBase)

### DDHelpers

This module defines some basic interfaces and classses, such as:
* `IDDModuleInterdae` -- interface of a module, dervied from `DDBase`;
* `helpers::` -- a collection of helper functions used throughtout `DDTools`;
* `DDModuleWidget` -- base widget class for a plugin.

### DDBlueprints

A module for exposing some DDTools functions to Blueprints.
> 😃 One can log using `DDLog` directly from Blueprint by using functions defined in [DD Blueprint Library](https://github.com/remap/DDTools/blob/master/Source/DDBlueprints/Public/DDBlueprintLibrary.h).

### DDManager

A (singleton) module which keeps track of all registered `DDBase` modules and provides interface to initialize and create module widgets.

### DDBase

`DDBase` is a base module class (derived from `IModuleInterface`) that implements some helpful functionality, such as:
* creates module-wide logger;
* automatically locates UI widget (derived from `DDModuleWidget`) shipped with the plugin and loads it;
* registers with `DDModuleManager`.

In order to properly initialize `DDBase`, one shall call `initModule()` method from within `StartupModule()` method:
```
void MyModule::StartupModule()
{
    initModule("MyModule", "<plugin version>");
    ...
}
```



