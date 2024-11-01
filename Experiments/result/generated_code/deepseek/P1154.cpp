#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    int* cows = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &cows[i]);
    }

    int K = 1;
    while (1) {
        int* buckets = (int*)calloc(K, sizeof(int));
        int conflict = 0;
        for (int i = 0; i < N; i++) {
            int bucket = cows[i] % K;
            if (buckets[bucket] > 0) {
                conflict = 1;
                break;
            }
            buckets[bucket]++;
        }
        free(buckets);
        if (!conflict) {
            printf("%d\n", K);
            break;
        }
        K++;
    }

    free(cows);
    return 0;
}