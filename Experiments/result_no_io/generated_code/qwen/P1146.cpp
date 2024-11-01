#include <stdio.h>
#include <stdlib.h>

void flip(int *coins, int N) {
    for (int i = 0; i < N - 1; i++) {
        coins[i] = 1 - coins[i];
    }
}

void printCoins(int *coins, int N) {
    for (int i = 0; i < N; i++) {
        printf("%d", coins[i]);
    }
    printf("\n");
}

int main() {
    int N;
    scanf("%d", &N);
    int *coins = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        coins[i] = 0;
    }

    int operations = 0;
    while (1) {
        int changed = 0;
        for (int i = 0; i < N - 1; i++) {
            if (coins[i] != coins[i + 1]) {
                flip(coins, N);
                changed = 1;
                break;
            }
        }
        if (!changed) {
            break;
        }
        operations++;
        printCoins(coins, N);
    }

    printf("%d\n", operations);

    free(coins);
    return 0;
}