#include "Scheduler.h"



// Tasks:

__TINYOS_RESULT __tinyOS_addTask(__TinyOS_Function taskFunc, unsigned long interval, __TINYOS_LAYER layer)
{
    if (__tinyOS_taskCount_ < sizeof(__tinyOS_tasks_) / sizeof(__tinyOS_tasks_[0]))
    {
        __tinyOS_tasks_[__tinyOS_taskCount_].taskFunction = taskFunc;

        __tinyOS_tasks_[__tinyOS_taskCount_].interval = interval;
        __tinyOS_tasks_[__tinyOS_taskCount_].previousMillis = get_millis(); // Start the task immediately
        __tinyOS_tasks_[__tinyOS_taskCount_].lifeTime = 0; // Controlled by uC timer - prevent from stuck

        __tinyOS_tasks_[__tinyOS_taskCount_].layer = layer;

        return __tinyOS_taskCount_++;
    }
    else {
        return -1;
    }
}

__TINYOS_RESULT __tinyOS_removeTask(int index, __TINYOS_LAYER layer)
{
    if (layer > __tinyOS_tasks_[index].layer)
        return __TINYOS_ERROR;

    if (index >= 0 && index < __tinyOS_taskCount_)
    {
        for (int i = index; i < __tinyOS_taskCount_ - 1; i++) {
            __tinyOS_tasks_[i] = __tinyOS_tasks_[i + 1];
        }

        return __tinyOS_taskCount_--;
    }
    else {
        return __TINYOS_ERROR;
    }
}


void __tinyOS_runTasks()
{
    while (__TINYOS_TRUE)
    {
        unsigned long _currentMillis = get_millis();

        for (int i = 0; i < __tinyOS_taskCount_; i++)
        {
            if (_currentMillis - __tinyOS_tasks_[i].previousMillis >= __tinyOS_tasks_[i].interval)
            {
                __tinyOS_tasks_[i].previousMillis = _currentMillis;
                __tinyOS_tasks_[i].taskFunction();
            }
        }
    }
}