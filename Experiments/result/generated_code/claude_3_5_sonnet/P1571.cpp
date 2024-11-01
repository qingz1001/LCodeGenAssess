#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int innovation[MAX_N], contribution[MAX_N];

    for (int i = 0; i < n; i++) {
        scanf("%d", &innovation[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d", &contribution[i]);
    }

    qsort(contribution, m, sizeof(int), compare);

    for (int i = 0; i < n; i++) {
        if (bsearch(&innovation[i], contribution, m, sizeof(int), compare) != NULL) {
            printf("%d ", innovation[i]);
        }
    }

    printf("\n");

    return 0;
}