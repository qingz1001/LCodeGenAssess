#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100000
#define MAX_FILENAME 30

typedef struct {
    char input[MAX_FILENAME];
    char output[MAX_FILENAME];
    int number;
} FileNamePair;

int compare(const void *a, const void *b) {
    return ((FileNamePair*)a)->number - ((FileNamePair*)b)->number;
}

void extractNumber(char *filename, int *number) {
    char *p = filename;
    while (*p) {
        if (*p >= '0' && *p <= '9') {
            *number = atoi(p);
            return;
        }
        p++;
    }
}

int main() {
    char targetInput[MAX_FILENAME], targetOutput[MAX_FILENAME];
    int startNumber = 0;
    FileNamePair files[MAX_FILES];
    int fileCount = 0;

    char firstLine[MAX_FILENAME * 2];
    fgets(firstLine, sizeof(firstLine), stdin);
    firstLine[strcspn(firstLine, "\n")] = 0;

    if (sscanf(firstLine, "%d", &startNumber) == 1) {
        strcpy(targetInput, "");
        strcpy(targetOutput, "");
    } else {
        sscanf(firstLine, "%s %s", targetInput, targetOutput);
    }

    while (scanf("%s %s", files[fileCount].input, files[fileCount].output) == 2) {
        extractNumber(files[fileCount].input, &files[fileCount].number);
        fileCount++;
    }

    qsort(files, fileCount, sizeof(FileNamePair), compare);

    for (int i = 0; i < fileCount; i++) {
        char newInput[MAX_FILENAME], newOutput[MAX_FILENAME];

        if (strlen(targetInput) > 0) {
            sprintf(newInput, "%.*s%d.%s", (int)(strchr(targetInput, '0') - targetInput), targetInput, i + startNumber, strrchr(targetInput, '.') + 1);
            sprintf(newOutput, "%.*s%d.%s", (int)(strchr(targetInput, '0') - targetInput), targetInput, i + startNumber, targetOutput);
        } else {
            char *dot = strrchr(files[i].input, '.');
            int prefixLen = dot - files[i].input;
            sprintf(newInput, "%.*s%d%s", prefixLen, files[i].input, i + startNumber + 1, dot);

            dot = strrchr(files[i].output, '.');
            prefixLen = dot - files[i].output;
            sprintf(newOutput, "%.*s%d%s", prefixLen, files[i].output, i + startNumber + 1, dot);
        }

        printf("%s %s\n", newInput, newOutput);
    }

    return 0;
}