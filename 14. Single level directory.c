#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 4096
void copy() {
    const char *source_file = "C:/Users/syedf/OneDrive - saveetha.com/C programming/first.txt"; //set the path where to create the file
    const char *destination_file = "C:/Users/syedf/OneDrive - saveetha.com/C programming/second.txt"; //aset the path where to copy the file
    // Open the source file for reading
    int source_fd = open(source_file, O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        return;
    }
    // Open the destination file for writing
    int dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(source_fd);
        return;
    }
    // Copy the file content
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;
    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(dest_fd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return;
        }
    }
    if (bytesRead < 0) {
        perror("Error reading from source file");
    }
    // Close the files
    close(source_fd);
    close(dest_fd);
    printf("File copied successfully.\n");
}
void create() {
    const char *file_path = "C:/Users/syedf/OneDrive - saveetha.com/C programming/first.txt"; //set as same as source path 
    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        perror("Error creating file");
        return;
    }
    fprintf(fp, "");  // Write empty content to create the file
    fclose(fp);
    printf("File created successfully.\n");
}

void deleteFile() {
    const char *file_path = "C:/Users/syedf/OneDrive - saveetha.com/C programming/first.txt"; //Set the file to be deleted
    if (remove(file_path) == 0) {
        printf("File deleted successfully.\n");
    } else {
        perror("Error deleting file");
    }
}

int main() {
    int choice;
    printf("1. Create\t2. Copy\t3. Delete\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            create();
            break;
        case 2:
            copy();
            break;
        case 3:
            deleteFile();
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
