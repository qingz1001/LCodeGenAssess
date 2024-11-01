#include <stdio.h>
#include <string.h>

#define MAX_N 100

void flip(int coins[], int n) {
    for (int i = 0; i < n; i++) {
        coins[i] = 1 - coins[i];
    }
}

void printCoins(int coins[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", coins[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    int coins[MAX_N] = {0};
    int operations = n;

    printf("%d\n", operations);

    for (int i = 0; i < n - 1; i++) {
        flip(coins, n);
        coins[i] = 0;
        printCoins(coins, n);
    }

    flip(coins, n);
    printCoins(coins, n);

    return 0;
}