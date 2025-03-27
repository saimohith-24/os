#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int main() {
    HANDLE hMapFile;
    LPCTSTR sharedMemoryName = "Local\\MySharedMemory";
    char *sharedMemory;
    // Create a file mapping object
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,  // Use paging file
        NULL,                  // Default security
        PAGE_READWRITE,        // Read/write access
        0,                     // Maximum object size (high-order DWORD)
        1024,                  // Maximum object size (low-order DWORD)
        sharedMemoryName);     // Name of the mapping object
    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }
    // Map the view of the file into the process's address space
    sharedMemory = (char *)MapViewOfFile(
        hMapFile,              // Handle to the map object
        FILE_MAP_ALL_ACCESS,    // Read/write access
        0,                     // File offset high
        0,                     // File offset low
        1024);                 // Number of bytes to map

    if (sharedMemory == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }
    // Write to shared memory
    printf("Enter some data to write to shared memory: ");
    fgets(sharedMemory, 1024, stdin);
    // Print the written data
    printf("You wrote: %s\n", sharedMemory);
    // Unmap the shared memory from the process's address space
    UnmapViewOfFile(sharedMemory);
    // Close the handle to the file mapping object
    CloseHandle(hMapFile);
    return 0;
}
