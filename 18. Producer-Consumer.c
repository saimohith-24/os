#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define BUFFER_SIZE 5
#define MAX_ITEMS 10 // Maximum number of items to be produced/consumed
int buffer[BUFFER_SIZE]; // Shared buffer
HANDLE empty, full; // Semaphores for synchronization
int produced_items = 0, consumed_items = 0;
// Producer function
DWORD WINAPI producer(LPVOID arg) {
    while (produced_items < MAX_ITEMS) {
        WaitForSingleObject(empty, INFINITE); // Wait for an empty slot in the buffer
        // Critical section: add item to the buffer
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            if (buffer[i] == 0) {
                buffer[i] = produced_items + 1;
                printf("Produced: %d\n", buffer[i]);
                produced_items++;
                break;
            }
        }
        ReleaseSemaphore(full, 1, NULL); // Signal that an item has been produced
        Sleep(1000); // Sleep for a while to simulate time taken for producing
    }
    return 0;
}
// Consumer function
DWORD WINAPI consumer(LPVOID arg) {
    while (consumed_items < MAX_ITEMS) {
        WaitForSingleObject(full, INFINITE); // Wait for a filled slot in the buffer
        // Critical section: remove item from the buffer
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            if (buffer[i] != 0) {
                printf("Consumed: %d\n", buffer[i]);
                buffer[i] = 0; // Item consumed
                consumed_items++;
                break;
            }
        }
        ReleaseSemaphore(empty, 1, NULL); // Signal that an item has been consumed
        Sleep(2000); // Sleep for a while to simulate time taken for consuming
    }
    return 0;
}
int main() {
    // Initialize semaphores
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL); // Initially, BUFFER_SIZE empty slots
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL); // Initially, 0 filled slots
    // Create producer and consumer threads
    DWORD producerID, consumerID;
    HANDLE producerThread = CreateThread(NULL, 0, producer, NULL, 0, &producerID);
    HANDLE consumerThread = CreateThread(NULL, 0, consumer, NULL, 0, &consumerID);
    // Wait for both threads to finish
    WaitForSingleObject(producerThread, INFINITE);
    WaitForSingleObject(consumerThread, INFINITE);
    // Close handles
    CloseHandle(producerThread);
    CloseHandle(consumerThread);
    CloseHandle(empty);
    CloseHandle(full);
    return 0;
}
