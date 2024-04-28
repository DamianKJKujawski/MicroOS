#pragma once

#include "MicroOS_Definitions.h"
#include "Time.h"
#include "ContextSwitching.h"

extern bool ContextSwitchg_SwitchThread();



typedef void(*__MICROOS_Function)();

struct __MICROOS_Task
{
    __MICROOS_Function taskFunction;         // Pointer to the Task Function

    unsigned long interval;                 // Interval
    unsigned long previousMillis;           // Last time the Task was executed
    unsigned long lifeTime;

    __MICROOS_LAYER layer;
};



// Tasks management:
static struct __MICROOS_Task __MICROOS_tasks_[10];

static __MICROOS_BYTE __MICROOS_taskCount_ = 0;

__MICROOS_RESULT __MICROOS_addTask(__MICROOS_Function taskFunc, unsigned long interval, __MICROOS_LAYER layer);
__MICROOS_RESULT __MICROOS_removeTask(int index, __MICROOS_LAYER layer);

void __MICROOS_runTasks();