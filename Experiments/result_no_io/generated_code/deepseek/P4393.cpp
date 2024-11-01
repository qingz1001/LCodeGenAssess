#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    long long total_cost = 0;
    for (int i = 0; i < n - 1; i++) {
        total_cost += (long long)a[i] > (long long)a[i + 1] ? a[i] : a[i + 1];
    }

    printf("%lld\n", total_cost);
    free(a);
    return 0;
}