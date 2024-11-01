#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int location;
    int feed;
    int cost;
} Store;

int compare(const void *a, const void *b) {
    Store *storeA = (Store *)a;
    Store *storeB = (Store *)b;
    return storeA->location - storeB->location;
}

int main() {
    int K, N, E;
    scanf("%d %d %d", &K, &N, &E);

    Store stores[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &stores[i].location, &stores[i].feed, &stores[i].cost);
    }

    qsort(stores, N, sizeof(Store), compare);

    int dp[E + 1][K + 1];
    for (int i = 0; i <= E; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = 0x3f3f3f3f; // Initialize with a large number
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = stores[i].location; j <= E; j++) {
            for (int k = stores[i].feed; k <= K; k++) {
                dp[j][k] = (dp[j][k] < dp[j - stores[i].location][k - stores[i].feed] + stores[i].location * k + stores[i].cost) ? dp[j][k] : dp[j - stores[i].location][k - stores[i].feed] + stores[i].location * k + stores[i].cost;
            }
        }
    }

    int minCost = 0x3f3f3f3f;
    for (int i = 0; i <= E; i++) {
        for (int j = 0; j <= K; j++) {
            minCost = (minCost < dp[i][j]) ? minCost : dp[i][j];
        }
    }

    printf("%d\n", minCost);
    return 0;
}