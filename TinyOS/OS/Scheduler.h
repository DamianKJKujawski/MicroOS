#pragma once

#include "TinyOS_Definitions.h"
#include "Time.h"
#include "ContextSwitching.h"

extern bool ContextSwitchg_SwitchThread();



typedef void(*__TinyOS_Function)();

struct __TinyOS_Task
{
    __TinyOS_Function taskFunction;         // Pointer to the Task Function

    unsigned long interval;                 // Interval
    unsigned long previousMillis;           // Last time the Task was executed
    unsigned long lifeTime;

    __TINYOS_LAYER layer;
};



// Tasks management:
static struct __TinyOS_Task __tinyOS_tasks_[10];

static __TINYOS_BYTE __tinyOS_taskCount_ = 0;

__TINYOS_RESULT __tinyOS_addTask(__TinyOS_Function taskFunc, unsigned long interval, __TINYOS_LAYER layer);
__TINYOS_RESULT __tinyOS_removeTask(int index, __TINYOS_LAYER layer);

void __tinyOS_runTasks();