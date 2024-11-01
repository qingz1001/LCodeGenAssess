#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1000

long long powers[20];
long long sequence[MAX_N + 1];

int compare(const void *a, const void *b) {
    return (*(long long*)a - *(long long*)b);
}

int main() {
    int k, N;
    scanf("%d %d", &k, &N);

    int power_count = 0;
    long long p = 1;
    while (p <= 1e18) {
        powers[power_count++] = p;
        p *= k;
    }

    int seq_count = 0;
    for (int mask = 1; mask < (1 << power_count); mask++) {
        long long sum = 0;
        for (int j = 0; j < power_count; j++) {
            if (mask & (1 << j)) {
                sum += powers[j];
            }
        }
        sequence[seq_count++] = sum;
    }

    qsort(sequence, seq_count, sizeof(long long), compare);

    printf("%lld\n", sequence[N - 1]);

    return 0;
}