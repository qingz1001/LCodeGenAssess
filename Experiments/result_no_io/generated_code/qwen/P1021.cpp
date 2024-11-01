#include <stdio.h>
#include <stdlib.h>

#define MAX_N 15
#define MAX_K 15

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int *coins = (int *)malloc((N + K) * sizeof(int));
    for (int i = 0; i < N + K; i++) {
        coins[i] = i + 1;
    }

    int max_value = 0;
    int *result = (int *)malloc(N * sizeof(int));

    // Try all combinations of coin values
    for (int mask = 0; mask < (1 << (N + K)); mask++) {
        int count = 0;
        int current_value = 0;
        for (int i = 0; i < N + K; i++) {
            if (mask & (1 << i)) {
                result[count++] = coins[i];
                current_value += coins[i];
            }
        }

        if (count == N && current_value > max_value) {
            max_value = current_value;
        }
    }

    printf("1");
    for (int i = 1; i <= max_value; i++) {
        printf(" %d", i);
    }
    printf("\nMAX=%d\n", max_value);

    free(coins);
    free(result);

    return 0;
}