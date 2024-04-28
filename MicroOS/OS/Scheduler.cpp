#include "Scheduler.h"



// Tasks:

__MICROOS_RESULT __MICROOS_addTask(__MICROOS_Function taskFunc, unsigned long interval, __MICROOS_LAYER layer)
{
    if (__MICROOS_taskCount_ < sizeof(__MICROOS_tasks_) / sizeof(__MICROOS_tasks_[0]))
    {
        __MICROOS_tasks_[__MICROOS_taskCount_].taskFunction = taskFunc;

        __MICROOS_tasks_[__MICROOS_taskCount_].interval = interval;
        __MICROOS_tasks_[__MICROOS_taskCount_].previousMillis = get_millis(); // Start the task immediately
        __MICROOS_tasks_[__MICROOS_taskCount_].lifeTime = 0; // Controlled by uC timer - prevent from stuck

        __MICROOS_tasks_[__MICROOS_taskCount_].layer = layer;

        return __MICROOS_taskCount_++;
    }
    else {
        return -1;
    }
}

__MICROOS_RESULT __MICROOS_removeTask(int index, __MICROOS_LAYER layer)
{
    if (layer > __MICROOS_tasks_[index].layer)
        return __MICROOS_ERROR;

    if (index >= 0 && index < __MICROOS_taskCount_)
    {
        for (int i = index; i < __MICROOS_taskCount_ - 1; i++) {
            __MICROOS_tasks_[i] = __MICROOS_tasks_[i + 1];
        }

        return __MICROOS_taskCount_--;
    }
    else {
        return __MICROOS_ERROR;
    }
}


void __MICROOS_runTasks()
{
    while (__MICROOS_TRUE)
    {
        unsigned long _currentMillis = get_millis();

        for (int i = 0; i < __MICROOS_taskCount_; i++)
        {
            if (_currentMillis - __MICROOS_tasks_[i].previousMillis >= __MICROOS_tasks_[i].interval)
            {
                __MICROOS_tasks_[i].previousMillis = _currentMillis;
                __MICROOS_tasks_[i].taskFunction();
            }
        }
    }
}