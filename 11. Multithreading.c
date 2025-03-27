#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// Thread function
DWORD WINAPI myThreadFun(LPVOID lpParam)
{
    Sleep(1000); // Sleep for 1 second
    printf("Printing GeeksQuiz from Thread \n");
    return 0;
}
int main()
{
    HANDLE threadHandle;
    DWORD threadId;
    printf("Before Thread\n");
    // Create thread
    threadHandle = CreateThread(
        NULL,                  // Default security attributes
        0,                     // Default stack size
        myThreadFun,           // Thread function
        NULL,                  // Parameter to thread function
        0,                     // Default creation flags
        &threadId);            // Pointer to store thread ID
    // Check if thread creation succeeded
    if (threadHandle == NULL)
    {
        printf("Thread creation failed.\n");
        return 1;
    }
    // Wait for the thread to complete
    WaitForSingleObject(threadHandle, INFINITE);
    // Close the thread handle
    CloseHandle(threadHandle);
    printf("After Thread\n");
    return 0;
}
