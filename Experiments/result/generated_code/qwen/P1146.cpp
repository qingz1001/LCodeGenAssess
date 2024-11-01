#include <stdio.h>
#include <stdlib.h>

void flip(int *coins, int n) {
    for (int i = 0; i < n - 1; i++) {
        coins[i] = 1 - coins[i];
    }
}

void printCoins(int *coins, int n) {
    for (int i = 0; i < n; i++) {
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
        if (coins[0] == 0) {
            break;
        }
        flip(coins, N);
        printCoins(coins, N);
        operations++;
    }

    free(coins);
    return 0;
}