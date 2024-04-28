#pragma once

#include "MicroOS_Definitions.h"



#define INTERRUPT_NOP 0
#define INTERRUPT_TIMER 1
#define INTERRUPT_IO 2
#define INTERRUPT_NETWORK 3



__MICROOS_RESULT InterruptManager_Init();

__MICROOS_RESULT InterruptManager_WaitForInterrupt();

void InterruptManager_Task();