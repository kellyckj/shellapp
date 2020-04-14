//
// DDLog.cpp
//
//  Generated on January 27 2020
//  Template created by Peter Gusev on 27 January 2020.
//  Copyright 2013-2019 Regents of the University of California
//

#include "DDLog.h"

#define LOCTEXT_NAMESPACE "FDDLogModule"

using namespace std;
using namespace ddlog;

FDDLogModule::FDDLogModule() {}
FDDLogModule::~FDDLogModule() {}
void FDDLogModule::StartupModule() {}
void FDDLogModule::ShutdownModule() {}

void FDDLogModule::initLogger(std::string loggerName)
{
    newLogger(loggerName);
    logger_ = getLogger(loggerName);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDDLogModule, DDLog)
