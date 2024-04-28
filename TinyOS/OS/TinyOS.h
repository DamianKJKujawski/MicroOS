#pragma once

#include "Scheduler.h"
#include <iostream>

extern void __tinyOS_runTasks();



void Task_1();
void Task_2();

void __tinyOs_setupKernel();
void __tinyOs_setupUserTasks();