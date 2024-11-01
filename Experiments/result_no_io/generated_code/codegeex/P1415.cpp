#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return strcmp((char*)a, (char*)b);
}

int main() {
    char input[501];
    scanf("%s", input);

    int len = strlen(input);
    char **substrings = (char**)malloc(len * sizeof(char*));
    for (int i = 0; i < len; i++) {
        substrings[i] = (char*)malloc(501 * sizeof(char));
    }

    int count = 0;
    for (int i = 0; i < len; i++) {
        int j = i;
        while (j < len) {
            substrings[count][j - i] = input[j];
            substrings[count][j - i + 1] = '\0';
            j++;
            if (j == len || input[j] == ',') {
                count++;
                break;
            }
        }
        if (j == len) break;
    }

    qsort(substrings, count, sizeof(char*), compare);

    for (int i = 0; i < count; i++) {
        printf("%s", substrings[i]);
        if (i != count - 1) {
            printf(",");
        }
    }

    for (int i = 0; i < len; i++) {
        free(substrings[i]);
    }
    free(substrings);

    return 0;
}