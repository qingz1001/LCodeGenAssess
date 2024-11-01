#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    long long *logs = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &logs[i]);
    }

    long long left = 0, right = 0;
    for (int i = 0; i < n; i++) {
        if (logs[i] > right) {
            right = logs[i];
        }
    }

    while (left < right) {
        long long mid = (left + right + 1) / 2;
        long long total = 0;
        for (int i = 0; i < n; i++) {
            total += logs[i] / mid;
        }
        if (total >= k) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    printf("%lld\n", left);

    free(logs);
    return 0;
}