#include <stdio.h>
#include <string.h>
int main() {
    char fn[10], pat[10], temp[200];
    FILE *fp;
    printf("\nEnter file name: "); //Create the txt file and add some content, create in same directory where code compiled
    scanf("%s", fn);
    printf("Enter the pattern: "); //Enter any word from file patterns is matching
    scanf("%s", pat);
    fp = fopen(fn, "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", fn);
        return 1;
    }
    while (!feof(fp)) {
        fgets(temp, sizeof(temp), fp);
        if (strstr(temp, pat)) { // Check if the pattern exists in the line
            printf("%s", temp);
        }
    }
    fclose(fp);
    return 0;
}
