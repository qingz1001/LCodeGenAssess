#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int zi;
    int ai;
    int bi;
} Engine;

int compare(const void *a, const void *b) {
    return ((Engine *)b)->zi - ((Engine *)a)->zi;
}

long long minVoltage(int n, long long p, Engine engines[]) {
    qsort(engines, n, sizeof(Engine), compare);

    long long left = 0, right = 1e9;
    while (left < right) {
        long long mid = (left + right) / 2;
        long long totalPower = 0;

        for (int i = 0; i < n; i++) {
            if (mid <= engines[i].zi) {
                totalPower += (long long)engines[i].ai * mid;
            } else {
                totalPower += (long long)engines[i].ai * engines[i].zi +
                              (long long)engines[i].bi * (mid - engines[i].zi);
            }
        }

        if (totalPower >= p) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int main() {
    int n;
    long long p;
    scanf("%d %lld", &n, &p);

    Engine engines[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &engines[i].zi, &engines[i].ai, &engines[i].bi);
    }

    printf("%lld\n", minVoltage(n, p, engines));

    return 0;
}