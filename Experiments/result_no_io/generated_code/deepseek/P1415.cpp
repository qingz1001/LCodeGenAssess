#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 501

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void splitSequence(char *s) {
    int len = strlen(s);
    char *result[MAX_LEN];
    int result_count = 0;

    for (int i = 1; i <= len; i++) {
        char *part1 = strndup(s, i);
        char *part2 = s + i;

        if (part2[0] == '\0') {
            result[result_count++] = part1;
            continue;
        }

        char *temp_result[MAX_LEN];
        int temp_count = 0;
        splitSequence(part2);

        if (strcmp(part1, temp_result[0]) < 0) {
            result[result_count++] = part1;
            for (int j = 0; j < temp_count; j++) {
                result[result_count++] = temp_result[j];
            }
        } else {
            free(part1);
        }
    }

    qsort(result, result_count, sizeof(char *), compare);

    for (int i = 0; i < result_count; i++) {
        printf("%s", result[i]);
        if (i < result_count - 1) {
            printf(",");
        }
        free(result[i]);
    }
}

int main() {
    char s[MAX_LEN];
    scanf("%s", s);
    splitSequence(s);
    return 0;
}