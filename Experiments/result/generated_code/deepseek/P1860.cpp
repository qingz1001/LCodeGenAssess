#include <stdio.h>
#include <stdlib.h>

#define MAX_N 60
#define MAX_M 240
#define MAX_K 30

typedef struct {
    int buy_price;
    int sell_price;
} Potion;

typedef struct {
    int result;
    int num_ingredients;
    int ingredients[MAX_N];
} Magic;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, M, V, K;
    Potion potions[MAX_N];
    Magic magics[MAX_M];

    scanf("%d %d %d %d", &N, &M, &V, &K);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &potions[i].buy_price, &potions[i].sell_price);
    }

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &magics[i].result, &magics[i].num_ingredients);
        for (int j = 0; j < magics[i].num_ingredients; j++) {
            scanf("%d", &magics[i].ingredients[j]);
        }
    }

    int dp[MAX_K + 1][MAX_V + 1];
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j <= V; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][V] = 0;

    for (int k = 0; k < K; k++) {
        for (int v = 0; v <= V; v++) {
            if (dp[k][v] == -1) continue;
            for (int i = 0; i < N; i++) {
                if (v >= potions[i].buy_price) {
                    dp[k + 1][v - potions[i].buy_price] = max(dp[k + 1][v - potions[i].buy_price], dp[k][v] + potions[i].sell_price);
                }
            }
            for (int i = 0; i < M; i++) {
                int cost = 0;
                for (int j = 0; j < magics[i].num_ingredients; j++) {
                    cost += potions[magics[i].ingredients[j] - 1].buy_price;
                }
                if (v >= cost) {
                    dp[k + 1][v - cost] = max(dp[k + 1][v - cost], dp[k][v] + potions[magics[i].result - 1].sell_price);
                }
            }
        }
    }

    int max_profit = 0;
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j <= V; j++) {
            max_profit = max(max_profit, dp[i][j]);
        }
    }

    printf("%d\n", max_profit);

    return 0;
}