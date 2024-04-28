#include "DeviceManager.h"
#include "ContextSwitching.h"


__TINYOS_RESULT DeviceManager_Init()
{
	return __TINYOS_SUCCESS;
}


void DeviceManager_Task()
{
	while (ContextSwitchg_SwitchThread())
	{

	}
}