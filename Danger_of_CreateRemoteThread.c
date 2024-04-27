#include <windows.h>
#include <stdio.h>


DWORD WINAPI InjectedFunction(LPVOID param) 
{
    MessageBoxA(NULL, "Injected function works!", "Message", MB_OK);
    return 0;
}

int main() 
{
    DWORD pid = ...; // (Find Window/Process ID)

    // Obtain a handle to the target process:
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL) {
        printf("Failed to obtain handle to the target process.\n");
        return 1;
    }

    // Injecting code into the target process:
    LPVOID pRemoteThread = VirtualAllocEx(hProcess, NULL, 4096, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (pRemoteThread == NULL) 
	{
        printf("Failed to allocate memory in the target process.\n");
        CloseHandle(hProcess);
        return 1;
    }

    // Writing the function code to the target process memory:
    WriteProcessMemory(hProcess, pRemoteThread, &InjectedFunction, sizeof(InjectedFunction), NULL);

    // Creating a thread in the target process to start executing the injected function:
    HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pRemoteThread, NULL, 0, NULL);
    if (hRemoteThread == NULL) {
        printf("Failed to create a thread in the target process.\n");
        VirtualFreeEx(hProcess, pRemoteThread, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return 1;
    }

    // Waiting for the injected code to finish:
    WaitForSingleObject(hRemoteThread, INFINITE);

    // Freeing resources:
    VirtualFreeEx(hProcess, pRemoteThread, 0, MEM_RELEASE);
    CloseHandle(hRemoteThread);
    CloseHandle(hProcess);

    printf("Injected code has been executed in the target process.\n");

    return 0;
}
