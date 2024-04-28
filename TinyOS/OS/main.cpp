#include "TinyOS.h"



int main() 
{
    __tinyOs_setupKernel();
    __tinyOs_setupUserTasks();

    while (__TINYOS_TRUE) {
        __tinyOS_runTasks();
    }

    return 0;
}
