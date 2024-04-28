#include "InterruptManager.h"
#include "ContextSwitching.h"



__MICROOS_RESULT InterruptManager_Init()
{
    return __MICROOS_SUCCESS;
}

__MICROOS_RESULT InterruptManager_WaitForInterrupt()
{
    return INTERRUPT_NOP;
}

void InterruptManager_Task()
{
    while (ContextSwitchg_SwitchThread())
    {
        __MICROOS_RESULT _interruptType = InterruptManager_WaitForInterrupt();

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