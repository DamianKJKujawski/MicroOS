#include "InterruptManager.h"
#include "ContextSwitching.h"



__TINYOS_RESULT InterruptManager_Init()
{
    return __TINYOS_SUCCESS;
}

__TINYOS_RESULT InterruptManager_WaitForInterrupt()
{
    return INTERRUPT_NOP;
}

void InterruptManager_Task()
{
    while (ContextSwitchg_SwitchThread())
    {
        __TINYOS_RESULT _interruptType = InterruptManager_WaitForInterrupt();

        switch (_interruptType)
        {
            case INTERRUPT_TIMER:
                break;
            case INTERRUPT_IO:
                break;
            case INTERRUPT_NETWORK:
                break;
        }
    }
}