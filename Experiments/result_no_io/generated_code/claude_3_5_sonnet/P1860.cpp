#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 60
#define MAX_M 240
#define MAX_V 1000
#define MAX_K 30

int N, M, V, K;
int sell[MAX_N + 1], buy[MAX_N + 1];
int magic[MAX_M][MAX_N + 1];
int dp[MAX_K + 1][MAX_V + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d %d", &N, &M, &V, &K);
    
    for (int i = 1; i <= N; i++) {
        scanf("%d %d", &sell[i], &buy[i]);
    }
    
    for (int i = 0; i < M; i++) {
        int product, num_ingredients;
        scanf("%d %d", &product, &num_ingredients);
        magic[i][0] = product;
        for (int j = 1; j <= num_ingredients; j++) {
            scanf("%d", &magic[i][j]);
        }
        magic[i][num_ingredients + 1] = 0;
    }
    
    memset(dp, -0x3f, sizeof(dp));
    dp[0][V] = 0;
    
    for (int k = 1; k <= K; k++) {
        for (int v = 0; v <= V; v++) {
            dp[k][v] = dp[k-1][v];
            
            for (int i = 1; i <= N; i++) {
                if (v + sell[i] <= V) {
                    dp[k][v] = max(dp[k][v], dp[k-1][v + sell[i]] + buy[i]);
                }
            }
            
            for (int i = 0; i < M; i++) {
                int cost = 0;
                int valid = 1;
                for (int j = 1; magic[i][j] != 0; j++) {
                    cost += sell[magic[i][j]];
                    if (cost > v) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    dp[k][v] = max(dp[k][v], dp[k-1][v - cost] + sell[magic[i][0]]);
                }
            }
        }
    }
    
    int result = 0;
    for (int v = 0; v <= V; v++) {
        result = max(result, dp[K][v]);
    }
    
    printf("%d\n", result);
    
    return 0;
}