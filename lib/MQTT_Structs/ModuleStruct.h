#ifndef ModuleStruct_h
#define ModuleStruct_h

#include "Module.h"

struct ModuleStruct
{
    const char* moduleID;
    const char* moduleType;
    Module* mod = nullptr;
};

#endif