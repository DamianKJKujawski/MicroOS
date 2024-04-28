#pragma once

#include "TinyOS_Definitions.h"



//TODO: 
// 1. Add Stack Canary (Calculate Last SP)
// 2. Add DEP (Data Execution Prevention - Strictly define field of the process)
// 3. Code Signing (Simle - Based on CRC)



__TINYOS_RESULT SecurityManager_Init();

bool SecurityManager_Is_SecurityViolation();
void SecurityManager_Handle_SecurityViolation();

void SecurityManager_Task();