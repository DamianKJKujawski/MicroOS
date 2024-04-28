#include "TinyOS.h"

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


static void __tinyOs_Init()
{
    InterruptManager_Init();
    MemoryManager_Init();
    DeviceManager_Init();
    FileManager_Init();
    SecurityManager_Init();
}


void __tinyOs_setupKernel()
{
    __tinyOs_Init();

    __tinyOS_addTask(InterruptManager_Task, 0, __TINYOS_LAYER_KERNEL);
    __tinyOS_addTask(MemoryManager_Task, 0, __TINYOS_LAYER_KERNEL);
    __tinyOS_addTask(DeviceManager_Task, 0, __TINYOS_LAYER_KERNEL);
    __tinyOS_addTask(FileManager_Task, 0, __TINYOS_LAYER_KERNEL);
    __tinyOS_addTask(SecurityManager_Task, 0, __TINYOS_LAYER_KERNEL);
}

void __tinyOs_setupUserTasks()
{
    __tinyOS_addTask(Task_1, 2000, __TINYOS_LAYER_USER);
    __tinyOS_addTask(Task_2, 1000, __TINYOS_LAYER_USER);
}