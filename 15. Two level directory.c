#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char mainDirectory[] = "C:/Users/syedf/OneDrive - saveetha.com"; //set the path to create file
    char subDirectory[] = "C programming"; //the folder name where to create
    char fileName[] = "example.txt";
    char filePath[200];
    char mainDirPath[200];
    // Construct main directory path and file path
    snprintf(mainDirPath, sizeof(mainDirPath), "%s/%s/", mainDirectory, subDirectory);
    snprintf(filePath, sizeof(filePath), "%s%s", mainDirPath, fileName);
    // Open file for writing
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return 1;
    }
    // Write content to the file
    fprintf(file, "This is an example file content.");
    fclose(file);
    printf("File created successfully: %s\n", filePath);
    return 0;
}
