#include <stdio.h>

#define MAX_N 60
#define MAX_M 240
#define MAX_V 1000
#define MAX_K 30

int main() {
    int N, M, V, K;
    scanf("%d%d%d%d", &N, &M, &V, &K);

    int prices[MAX_N + 1][2]; // prices[i][0] is selling price, prices[i][1] is recycling price
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &prices[i][0], &prices[i][1]);
    }

    int recipes[MAX_M + 1][MAX_N + 1]; // recipes[i][j] is the j-th ingredient of the i-th recipe
    int recipe_counts[MAX_M + 1];
    for (int i = 1; i <= M; i++) {
        int product;
        scanf("%d", &product);
        scanf("%d", &recipe_counts[i]);
        for (int j = 1; j <= recipe_counts[i]; j++) {
            scanf("%d", &recipes[i][j]);
        }
    }

    // Initialize DP table
    int dp[MAX_V + 1][MAX_K + 1];
    for (int i = 0; i <= V; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = 0;
        }
    }

    // Process each recipe
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j <= V; j++) {
            for (int l = 0; l <= K; l++) {
                int product = recipes[i][0];
                int cost = 0;
                int new_k = l;
                for (int m = 1; m <= recipe_counts[i]; m++) {
                    int ingredient = recipes[i][m];
                    cost += prices[ingredient][0];
                    new_k++;
                }
                if (j >= cost && new_k <= K) {
                    dp[j][l] = dp[j][l] > dp[j - cost][new_k] + prices[product][1] - prices[product][0] ? dp[j][l] : dp[j - cost][new_k] + prices[product][1] - prices[product][0];
                }
            }
        }
    }

    // Find the maximum profit
    int max_profit = 0;
    for (int i = 0; i <= V; i++) {
        for (int j = 0; j <= K; j++) {
            max_profit = max_profit > dp[i][j] ? max_profit : dp[i][j];
        }
    }

    printf("%d\n", max_profit);

    return 0;
}