#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20
#define MAX_LEN 10

int compare(const void* a, const void* b) {
    char ab[MAX_LEN * 2 + 1], ba[MAX_LEN * 2 + 1];
    sprintf(ab, "%s%s", (char*)a, (char*)b);
    sprintf(ba, "%s%s", (char*)b, (char*)a);
    return strcmp(ba, ab);
}

int main() {
    int n;
    char numbers[MAX_N][MAX_LEN + 1];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", numbers[i]);
    }

    qsort(numbers, n, sizeof(numbers[0]), compare);

    for (int i = 0; i < n; i++) {
        printf("%s", numbers[i]);
    }
    printf("\n");

    return 0;
}