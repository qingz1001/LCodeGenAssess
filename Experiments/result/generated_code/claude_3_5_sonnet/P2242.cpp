#include <stdio.h>
#include <stdlib.h>

#define MAX_N 15000

long long holes[MAX_N];

int compare(const void *a, const void *b) {
    return (*(long long*)a - *(long long*)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &holes[i]);
    }

    qsort(holes, n, sizeof(long long), compare);

    long long *diff = malloc((n - 1) * sizeof(long long));
    for (int i = 0; i < n - 1; i++) {
        diff[i] = holes[i + 1] - holes[i];
    }

    qsort(diff, n - 1, sizeof(long long), compare);

    long long total_length = holes[n - 1] - holes[0];
    for (int i = 0; i < m - 1 && i < n - 1; i++) {
        total_length -= diff[n - 2 - i];
    }

    printf("%lld\n", total_length);

    free(diff);
    return 0;
}