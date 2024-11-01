#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20
#define MAXLEN 20

typedef struct {
    char code[MAXLEN];
    int len;
} Code;

int compare(const void *a, const void *b) {
    return strcmp(((Code *)a)->code, ((Code *)b)->code);
}

void mergeCodes(Code codes[], int n, Code result[]) {
    qsort(codes, n, sizeof(Code), compare);

    for (int i = 0; i < n; i++) {
        strcat(result[i].code, codes[i].code);
        result[i].len += codes[i].len;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Code codes[MAXN];
    Code result[MAXN];

    for (int i = 0; i < n; i++) {
        scanf("%s", codes[i].code);
        codes[i].len = strlen(codes[i].code);
        strcpy(result[i].code, codes[i].code);
        result[i].len = codes[i].len;
    }

    mergeCodes(codes, n, result);

    printf("%d\n", result[0].len);
    printf("%s\n", result[0].code);

    return 0;
}