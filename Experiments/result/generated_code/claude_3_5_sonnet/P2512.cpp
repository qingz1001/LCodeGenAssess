#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1000001

long long candy[MAX_N];
long long sum[MAX_N];

int cmp(const void *a, const void *b) {
    long long diff = *(long long*)a - *(long long*)b;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    long long total = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &candy[i]);
        total += candy[i];
    }

    long long avg = total / n;

    for (int i = 0; i < n; i++) {
        sum[i] = (i == 0) ? candy[0] - avg : sum[i-1] + candy[i] - avg;
    }

    qsort(sum, n, sizeof(long long), cmp);

    long long mid = sum[n/2];
    long long result = 0;

    for (int i = 0; i < n; i++) {
        result += llabs(sum[i] - mid);
    }

    printf("%lld\n", result);

    return 0;
}