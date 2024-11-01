#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, m;
    scanf("%d", &n);
    int cakes[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &cakes[i]);
    }
    scanf("%d", &m);
    int mouths[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &mouths[i]);
    }

    qsort(cakes, n, sizeof(int), compare);
    qsort(mouths, m, sizeof(int), compare);

    int count = 0;
    int j = 0;
    for (int i = 0; i < m; i++) {
        while (j < n && cakes[j] < mouths[i]) {
            j++;
        }
        if (j < n) {
            count++;
            j++;
        } else {
            break;
        }
    }

    printf("%d\n", count);
    return 0;
}