#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    int min_gifts = k;
    while (min_gifts < n && a[min_gifts] == a[min_gifts - 1]) {
        min_gifts++;
    }

    printf("%d\n", min_gifts);
    return 0;
}