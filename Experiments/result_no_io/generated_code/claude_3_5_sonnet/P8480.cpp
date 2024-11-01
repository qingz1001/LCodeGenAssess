#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000
#define MAX_M 10

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    long long a[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    long long max_val = a[0], min_val = a[0];
    for (int i = 1; i < n; i++) {
        max_val = max(max_val, a[i]);
        min_val = min(min_val, a[i]);
    }

    for (int i = 0; i < m; i++) {
        long long new_max = max(max_val + 2, max_val * 2);
        long long new_min = min(min_val - 2, min_val / 2);
        max_val = new_max;
        min_val = new_min;
    }

    printf("%lld\n", max_val - min_val);

    return 0;
}