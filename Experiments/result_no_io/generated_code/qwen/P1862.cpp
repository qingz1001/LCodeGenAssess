#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    scanf("%d", &n);

    int x[10000];
    for (int i = 0; i < n; i++) {
        scanf("%d %*d", &x[i]);
    }

    qsort(x, n, sizeof(int), compare);

    long long total_length = 0;
    for (int i = 0; i < n; i++) {
        total_length += (long long)x[i] * (i + 1) - (long long)x[i] * (n - i);
    }

    printf("%lld\n", abs(total_length));

    return 0;
}