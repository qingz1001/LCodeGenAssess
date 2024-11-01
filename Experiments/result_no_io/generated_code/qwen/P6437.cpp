#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    int max_sum = 0;
    for (int i = 0; i < n - 2; i++) {
        if (a[i] + a[i + 1] + a[i + 2] > m) break;
        max_sum = a[i] + a[i + 1] + a[i + 2];
    }

    printf("%d\n", max_sum);
    return 0;
}