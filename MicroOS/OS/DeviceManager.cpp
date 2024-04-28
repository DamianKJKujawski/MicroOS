#include "DeviceManager.h"
#include "ContextSwitching.h"


__MICROOS_RESULT DeviceManager_Init()
{
	return __MICROOS_SUCCESS;
}


void DeviceManager_Task()
{
	while (ContextSwitchg_SwitchThread())
	{

	}
}