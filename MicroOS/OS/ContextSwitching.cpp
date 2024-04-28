#include "ContextSwitching.h"

#ifdef ESP32

#include <stdio.h>
#include <setjmp.h>

#define STACK_SIZE 1024

typedef struct {
    jmp_buf context;
    char stack[STACK_SIZE];
} Thread;

Thread thread1, thread2;
Thread* current_thread;

void thread1_func();
void thread2_func();
void switch_thread(Thread* next_thread);

int contextLoop()
{
    // Inicjalizacja w¹tków:
    if (setjmp(thread1.context) == 0) {
        thread1_func();
    }
    if (setjmp(thread2.context) == 0) {
        thread2_func();
    }

    // Ustawienie w¹tku pocz¹tkowego:
    current_thread = &thread1;
    longjmp(current_thread->context, 1);

    return 0;
}

void thread1_func()
{
    while (1)
    {
        printf("Thread 1\n");
        switch_thread(&thread2);
    }
}

void thread2_func()
{
    while (1)
    {
        printf("Thread 2\n");
        switch_thread(&thread1);
    }
}

void switch_thread(Thread* next_thread)
{
    // asm volatile("mov sp, %[next_sp]" : : [next_sp] "r" (next_thread->sp));
    if (setjmp(current_thread->context) == 0)
    {
        current_thread = next_thread;
        longjmp(current_thread->context, 1);
    }

    // asm volatile("ret");
}

#endif

bool ContextSwitchg_SwitchThread()
{
    // switch_thread(Thread* next_thread) 

    return false;
}