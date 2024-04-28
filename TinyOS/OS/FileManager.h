#pragma once

#include "TinyOS_Definitions.h"



#define FILE_NOP 0
#define FILE_OPEN 1
#define FILE_CLOSE 2
#define FILE_READ 3
#define FILE_WRITE 4



__TINYOS_RESULT FileManager_Init();

__TINYOS_RESULT FileManager_WaitForEvent();

void FileManager_Task();
