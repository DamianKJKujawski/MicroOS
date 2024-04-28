#include "MicroOS.h"

#include "InterruptManager.h"
#include "MemoryManager.h"
#include "DeviceManager.h"
#include "FileManager.h"
#include "SecurityManager.h"



void Task_1()
{
    std::cout << "Task 1 executed!" << std::endl;
}

void Task_2()
{
    std::cout << "Task 2 executed!" << std::endl;
}


static void __MICROOS_Init()
{
    InterruptManager_Init();
    MemoryManager_Init();
    DeviceManager_Init();
    FileManager_Init();
    SecurityManager_Init();
}


void __MICROOS_setupKernel()
{
    __MICROOS_Init();

    __MICROOS_addTask(InterruptManager_Task, 0, __MICROOS_LAYER_KERNEL);
    __MICROOS_addTask(MemoryManager_Task, 0, __MICROOS_LAYER_KERNEL);
    __MICROOS_addTask(DeviceManager_Task, 0, __MICROOS_LAYER_KERNEL);
    __MICROOS_addTask(FileManager_Task, 0, __MICROOS_LAYER_KERNEL);
    __MICROOS_addTask(SecurityManager_Task, 0, __MICROOS_LAYER_KERNEL);
}

void __MICROOS_setupUserTasks()
{
    __MICROOS_addTask(Task_1, 2000, __MICROOS_LAYER_USER);
    __MICROOS_addTask(Task_2, 1000, __MICROOS_LAYER_USER);
}