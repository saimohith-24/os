#include <windows.h>
#include <stdio.h>
DWORD WINAPI func(LPVOID arg) {
    printf("Inside the thread\n");
    return 0;
}
int main() {
    HANDLE thread = CreateThread(NULL, 0, func, NULL, 0, NULL);
    if (thread == NULL) {
        printf("Error creating thread\n");
        return 1;
    }
    printf("This line may be printed before thread terminates\n");
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    printf("This line will be printed after thread ends\n");
    return 0;
}
