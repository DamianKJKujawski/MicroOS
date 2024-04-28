#include "MicroOS.h"



int main() 
{
    __MICROOS_setupKernel();
    __MICROOS_setupUserTasks();

    while (__MICROOS_TRUE) {
        __MICROOS_runTasks();
    }

    return 0;
}
