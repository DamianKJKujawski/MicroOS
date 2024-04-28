#pragma once

#include "TinyOS_Definitions.h"



#define INTERRUPT_NOP 0
#define INTERRUPT_TIMER 1
#define INTERRUPT_IO 2
#define INTERRUPT_NETWORK 3



__TINYOS_RESULT InterruptManager_Init();

__TINYOS_RESULT InterruptManager_WaitForInterrupt();

void InterruptManager_Task();