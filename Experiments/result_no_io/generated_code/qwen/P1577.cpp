#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(float*)a - *(float*)b);
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    float lengths[N];
    for (int i = 0; i < N; i++) {
        scanf("%f", &lengths[i]);
    }

    qsort(lengths, N, sizeof(float), compare);

    float low = 0.00, high = lengths[N-1], mid;
    while (high - low > 0.01) {
        mid = (low + high) / 2.0;
        int count = 0;
        for (int i = 0; i < N; i++) {
            count += lengths[i] / mid;
        }
        if (count >= K) {
            low = mid;
        } else {
            high = mid;
        }
    }

    printf("%.2f\n", low);

    return 0;
}