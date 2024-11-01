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
    int min_val = INT_MAX;

    for (int i = 0; i < n - 1; i++) {
        int cost = a[i] > a[i + 1] ? a[i] : a[i + 1];
        total_cost += cost;
        if (cost < min_val) {
            min_val = cost;
        }
    }

    total_cost -= min_val;

    printf("%lld\n", total_cost);

    free(a);
    return 0;
}