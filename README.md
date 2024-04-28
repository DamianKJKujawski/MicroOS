### MicroOS Template

Template for a simple OS designed for ESP32/ ATmega.

![MicroOS](https://github.com/DamianKJKujawski/TinyOS/assets/160174331/4f0a33c8-c478-4984-ba18-c1bda71e95c3)

### RISKS ASSOCIATED WITH THE CreateRemoteThread FUNCTION IN WINDOWS:

Introduction:
The CreateRemoteThread function is a powerful tool in the Windows operating system, allowing the creation of threads within the address space of another process. Despite its positive uses in low-level programming, this function carries potential security risks.

Arguments:

- Malicious code injection: The CreateRemoteThread function can be exploited by malicious software to inject malicious code into other processes. By using this function, malicious programs can gain control over other processes, leading to privacy breaches, data theft, or system damage.
- Substitution of system functions: Attackers can utilize the CreateRemoteThread function to substitute existing system functions in other processes. By injecting malicious code into the target process and forcing the execution of the modified function, attackers can deceive the operating system and perform malicious actions such as data theft or user surveillance.
- Bypassing system protections: Employing the CreateRemoteThread function allows attackers to bypass system protections such as Data Execution Prevention (DEP) or Address Space Layout Randomization (ASLR). By injecting code into processes, attackers can execute malicious actions within the context of other processes, making it difficult to detect and defend against attacks.
- Potential consequences for system security: The use of the CreateRemoteThread function for malicious purposes can lead to serious consequences for the security of the Windows system, including data loss, privacy breaches, software damage, or even system crashes. Attackers can leverage this function to carry out various types of attacks, such as keylogging, ransomware, or spyware.

Conclusions:
Despite its useful application in low-level programming, the CreateRemoteThread function poses a potential threat to Windows system security. To prevent malicious exploitation of this function, appropriate security measures such as restrictions on process access permissions, monitoring of process activity, and regular system updates to patch security vulnerabilities are necessary. Additionally, educating users about the risks associated with the CreateRemoteThread function can help prevent attacks and safeguard system security.

EXAMPLE:

```

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
    if (pRemoteThread == NULL) {
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

```
