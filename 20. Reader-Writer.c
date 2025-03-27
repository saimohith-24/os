#include <stdio.h>
#include <windows.h>
#include <process.h>
HANDLE mutex, writeBlock;
int data = 0, readersCount = 0;
unsigned __stdcall reader(void *arg) {
    int i = 0;
    while (i < 10) {
        WaitForSingleObject(mutex, INFINITE);
        readersCount++;
        if (readersCount == 1) {
            WaitForSingleObject(writeBlock, INFINITE);
        }
        ReleaseMutex(mutex);
        // Reading operation
        printf("Reader reads data: %d\n", data);
        WaitForSingleObject(mutex, INFINITE);
        readersCount--;
        if (readersCount == 0) {
            ReleaseMutex(writeBlock);
        }
        ReleaseMutex(mutex);
        i++;
    }
    return 0;
}
unsigned __stdcall writer(void *arg) {
    int i = 0;
    while (i < 10) {
        WaitForSingleObject(writeBlock, INFINITE);
        // Writing operation
        data++;
        printf("Writer writes data: %d\n", data);
        ReleaseMutex(writeBlock);
        i++;
    }
    return 0;
}
int main() {
    HANDLE readerThread, writerThread;
    // Initialize synchronization primitives
    mutex = CreateMutex(NULL, FALSE, NULL);
    writeBlock = CreateMutex(NULL, FALSE, NULL);
    // Create reader and writer threads
    readerThread = (HANDLE)_beginthreadex(NULL, 0, reader, NULL, 0, NULL);
    writerThread = (HANDLE)_beginthreadex(NULL, 0, writer, NULL, 0, NULL);
    // Wait for threads to complete
    WaitForSingleObject(readerThread, INFINITE);
    WaitForSingleObject(writerThread, INFINITE);
    // Close thread and synchronization handles
    CloseHandle(readerThread);
    CloseHandle(writerThread);
    CloseHandle(mutex);
    CloseHandle(writeBlock);
    return 0;
}
