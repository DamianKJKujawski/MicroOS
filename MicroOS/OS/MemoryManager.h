#pragma once

#include "MicroOS_Definitions.h"



__MICROOS_RESULT MemoryManager_Init();

__MICROOS_RESULT MemoryManager_Is_MemoryFull();
__MICROOS_RESULT MemoryManager_Is_PageFault();
__MICROOS_RESULT MemoryManager_HandlePageFault();

void MemoryManager_Task();
