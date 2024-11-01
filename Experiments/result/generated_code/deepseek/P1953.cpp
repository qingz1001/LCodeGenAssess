#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char input[22];
    char output[22];
    int index;
} FilePair;

int compare(const void *a, const void *b) {
    return ((FilePair *)a)->index - ((FilePair *)b)->index;
}

int main() {
    char targetFormat[22];
    char targetExt[22];
    int changeFormat;
    int n;

    if (scanf("%s", targetFormat) == 1) {
        if (targetFormat[0] >= '0' && targetFormat[0] <= '9') {
            changeFormat = atoi(targetFormat);
            scanf("%d", &n);
        } else {
            changeFormat = 0;
            strcpy(targetExt, targetFormat + strlen(targetFormat) - 3);
            targetFormat[strlen(targetFormat) - 4] = '\0';
            scanf("%s", targetExt);
            scanf("%d", &n);
        }
    }

    FilePair *files = (FilePair *)malloc(n * sizeof(FilePair));
    for (int i = 0; i < n; i++) {
        scanf("%s %s", files[i].input, files[i].output);
        char *dot = strrchr(files[i].input, '.');
        *dot = '\0';
        files[i].index = atoi(dot + 1);
    }

    qsort(files, n, sizeof(FilePair), compare);

    for (int i = 0; i < n; i++) {
        if (changeFormat) {
            printf("%s%d %s%d\n", files[i].input, i + changeFormat, files[i].output, i + changeFormat);
        } else {
            printf("%s%d.%s %s%d.%s\n", targetFormat, i, targetExt, targetFormat, i, targetExt);
        }
    }

    free(files);
    return 0;
}