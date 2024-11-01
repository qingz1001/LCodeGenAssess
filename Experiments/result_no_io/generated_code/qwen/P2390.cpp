#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int t, n;
    scanf("%d %d", &t, &n);
    int x[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    qsort(x, n, sizeof(int), compare);

    int max_visits = 0;
    for (int i = 0; i < n; i++) {
        if (2 * x[i] <= t) {
            max_visits++;
        }
    }

    printf("%d\n", max_visits);

    return 0;
}