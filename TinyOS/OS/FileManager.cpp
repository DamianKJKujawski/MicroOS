#include "FileManager.h"
#include "ContextSwitching.h"



__TINYOS_RESULT FileManager_Init()
{
    return __TINYOS_SUCCESS;
}

__TINYOS_RESULT FileManager_WaitForEvent()
{
    return FILE_NOP;
}

void FileManager_Task()
{
    while (ContextSwitchg_SwitchThread())
    {
        __TINYOS_RESULT _fileSystemEvent = FileManager_WaitForEvent();

        switch (_fileSystemEvent)
        {
        case FILE_OPEN:
            break;
        case FILE_CLOSE:
            break;
        case FILE_READ:
            break;
        case FILE_WRITE:
            break;
        }
    }
}