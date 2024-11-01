#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 20
#define MAX_LEN 20

typedef struct {
    char str[MAX_LEN + 1];
    int len;
} Code;

Code codes[MAX_N];
int n;

int compare(const void *a, const void *b) {
    Code *codeA = (Code *)a;
    Code *codeB = (Code *)b;
    return strcmp(codeA->str, codeB->str);
}

int canForm(char *target, int targetLen, int start) {
    if (start == targetLen) return 1;
    for (int i = 0; i < n; i++) {
        if (strncmp(target + start, codes[i].str, codes[i].len) == 0) {
            if (canForm(target, targetLen, start + codes[i].len)) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", codes[i].str);
        codes[i].len = strlen(codes[i].str);
    }

    qsort(codes, n, sizeof(Code), compare);

    int minLen = 2 * MAX_LEN;
    char result[2 * MAX_LEN + 1] = "";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char target[2 * MAX_LEN + 1];
            strcpy(target, codes[i].str);
            strcat(target, codes[j].str);
            int targetLen = codes[i].len + codes[j].len;

            if (targetLen < minLen && canForm(target, targetLen, 0)) {
                minLen = targetLen;
                strcpy(result, target);
            } else if (targetLen == minLen && strcmp(target, result) < 0) {
                strcpy(result, target);
            }
        }
    }

    printf("%d\n%s\n", minLen, result);

    return 0;
}