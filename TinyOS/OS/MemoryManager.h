#pragma once

#include "TinyOS_Definitions.h"



__TINYOS_RESULT MemoryManager_Init();

__TINYOS_RESULT MemoryManager_Is_MemoryFull();
__TINYOS_RESULT MemoryManager_Is_PageFault();
__TINYOS_RESULT MemoryManager_HandlePageFault();

void MemoryManager_Task();
