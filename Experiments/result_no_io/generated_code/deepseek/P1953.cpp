#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 22
#define MAX_FILES 100000

typedef struct {
    char input[MAX_FILENAME_LEN];
    char output[MAX_FILENAME_LEN];
    int index;
} FileInfo;

int compare(const void *a, const void *b) {
    return ((FileInfo *)a)->index - ((FileInfo *)b)->index;
}

int extractNumber(char *filename) {
    int len = strlen(filename);
    for (int i = len - 1; i >= 0; i--) {
        if (filename[i] >= '0' && filename[i] <= '9') {
            return atoi(filename + i);
        }
    }
    return -1; // Should never happen
}

void generateNewFilename(char *newFilename, const char *prefix, const char *suffix, int index) {
    sprintf(newFilename, "%s%d.%s", prefix, index, suffix);
}

int main() {
    char format[MAX_FILENAME_LEN];
    int n;
    FileInfo files[MAX_FILES];

    // Read the format or number
    if (scanf("%s", format) != 1) {
        return 1;
    }

    // Check if the format is a number
    int startIndex = 0;
    if (format[0] >= '0' && format[0] <= '9') {
        startIndex = atoi(format);
    } else {
        // Read the second part of the format
        char suffix[MAX_FILENAME_LEN];
        if (scanf("%s", suffix) != 1) {
            return 1;
        }
        strcpy(format + strlen(format), ".");
        strcat(format, suffix);
    }

    // Read the number of files
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    // Read the file names and extract indices
    for (int i = 0; i < n; i++) {
        if (scanf("%s %s", files[i].input, files[i].output) != 2) {
            return 1;
        }
        files[i].index = extractNumber(files[i].input);
    }

    // Sort files by index
    qsort(files, n, sizeof(FileInfo), compare);

    // Generate new file names
    for (int i = 0; i < n; i++) {
        char newInput[MAX_FILENAME_LEN], newOutput[MAX_FILENAME_LEN];
        if (startIndex == 0 || startIndex == 1) {
            generateNewFilename(newInput, files[i].input, "in", i + startIndex);
            generateNewFilename(newOutput, files[i].output, "out", i + startIndex);
        } else {
            char prefix[MAX_FILENAME_LEN], suffix[MAX_FILENAME_LEN];
            sscanf(format, "%[^0-9]%s", prefix, suffix);
            generateNewFilename(newInput, prefix, "in", i);
            generateNewFilename(newOutput, prefix, "out", i);
        }
        printf("%s %s\n", newInput, newOutput);
    }

    return 0;
}