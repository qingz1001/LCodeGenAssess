#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int cakes[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &cakes[i]);
    }

    qsort(cakes, n, sizeof(int), compare);

    int m;
    scanf("%d", &m);
    int mouths[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &mouths[i]);
    }

    qsort(mouths, m, sizeof(int), compare);

    int count = 0;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (cakes[i] >= mouths[j]) {
            count++;
            i++;
            j++;
        } else {
            i++;
        }
    }

    printf("%d\n", count);

    return 0;
}