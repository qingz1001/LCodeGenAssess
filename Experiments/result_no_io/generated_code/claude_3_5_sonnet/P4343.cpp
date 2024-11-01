#include <stdio.h>
#include <stdlib.h>

#define MAX_L 100000

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    int l, k;
    scanf("%d %d", &l, &k);

    long long x[MAX_L];
    for (int i = 0; i < l; i++) {
        scanf("%lld", &x[i]);
    }

    long long sum = 0;
    long long maxSum = 0;
    int count = 0;
    long long minN = 1, maxN = 1000000000;

    for (int i = 0; i < l; i++) {
        sum += x[i];
        sum = max(sum, 0);
        maxSum = max(maxSum, sum);

        if (sum == 0) {
            count++;
        }
    }

    if (count + 1 < k) {
        printf("-1\n");
        return 0;
    }

    minN = maxSum + 1;

    long long current = 0;
    for (int i = l - 1; i >= 0; i--) {
        current += x[i];
        if (current <= 0) {
            current = 0;
            continue;
        }
        maxN = min(maxN, current);
    }

    if (minN > maxN) {
        printf("-1\n");
    } else {
        printf("%lld %lld\n", minN, maxN);
    }

    return 0;
}