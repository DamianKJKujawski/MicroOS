#include "SecurityManager.h"
#include "ContextSwitching.h"



__TINYOS_RESULT SecurityManager_Init()
{
	return __TINYOS_SUCCESS;
}


bool SecurityManager_Is_SecurityViolation()
{
	return false;
}

void SecurityManager_Handle_SecurityViolation()
{

}


void SecurityManager_Task()
{
	while (ContextSwitchg_SwitchThread())
	{
		if (SecurityManager_Is_SecurityViolation()) {
			SecurityManager_Handle_SecurityViolation();
		}
	}
}