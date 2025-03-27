#include <stdio.h>
#include <stdlib.h>
#include <io.h>      // For _open, _read, _write, _close
#include <fcntl.h>   // For O_RDWR, O_CREAT, O_APPEND, etc.
int main() {
    int fd;
    char buffer[100];
    // Creating a new file
    fd = _creat("sample.txt", 0666); //_S_IREAD | _S_IWRITE can use instead of 0666
    if (fd == -1) {
        perror("create");
        exit(1);
    } else {
        printf("File 'sample.txt' created successfully.\n");
        _close(fd);
    }
    // Opening an existing file for writing
    fd = _open("sample.txt", _O_WRONLY | _O_APPEND);
    if (fd == -1) {
        perror("open");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for writing.\n");
    }
    // Writing data to the file
    if (_write(fd, "Hello, World!\n", 14) == -1) {
        perror("write");
        exit(1);
    }
    printf("Data written to 'sample.txt'.\n");
    _close(fd);
    // Opening the file for reading
    fd = _open("sample.txt", _O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for reading.\n");
    }
    // Reading data from the file
    int bytesRead = _read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("read");
        exit(1);
    } else {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        printf("Data read from 'sample.txt':\n%s", buffer);
    }
    _close(fd);
    // Deleting the file
    if (remove("sample.txt") == -1) {
        perror("remove");
        exit(1);
    } else {
        printf("File 'sample.txt' deleted.\n");
    }
    return 0;
}
