#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000000

long long a[MAXN];
long long sum[MAXN];

long long min(long long x, long long y) {
    return x < y ? x : y;
}

int main() {
    int n;
    scanf("%d", &n);
    
    long long total = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        total += a[i];
    }
    
    long long avg = total / n;
    sum[0] = a[0] - avg;
    for (int i = 1; i < n; i++) {
        sum[i] = sum[i - 1] + a[i] - avg;
    }
    
    qsort(sum, n, sizeof(long long), (int (*)(const void *, const void *))strcmp);
    
    long long median = sum[n / 2];
    long long cost = 0;
    for (int i = 0; i < n; i++) {
        cost += llabs(sum[i] - median);
    }
    
    printf("%lld\n", cost);
    
    return 0;
}