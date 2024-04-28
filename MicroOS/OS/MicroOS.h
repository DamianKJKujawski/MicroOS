#pragma once

#include "Scheduler.h"
#include <iostream>

extern void __MICROOS_runTasks();



void Task_1();
void Task_2();

void __MICROOS_setupKernel();
void __MICROOS_setupUserTasks();