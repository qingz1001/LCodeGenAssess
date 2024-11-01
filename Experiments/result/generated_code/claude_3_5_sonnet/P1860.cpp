#include <stdio.h>
#include <string.h>
#define MAX_N 60
#define MAX_M 240
#define MAX_V 1000

int N, M, V, K;
int sell[MAX_N + 1], buy[MAX_N + 1];
int magic[MAX_M][MAX_N + 1];
int dp[MAX_V + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d %d", &N, &M, &V, &K);
    
    for (int i = 1; i <= N; i++) {
        scanf("%d %d", &sell[i], &buy[i]);
    }
    
    for (int i = 0; i < M; i++) {
        int product, count;
        scanf("%d %d", &product, &count);
        magic[i][0] = product;
        for (int j = 1; j <= count; j++) {
            scanf("%d", &magic[i][j]);
        }
    }
    
    memset(dp, -0x3f, sizeof(dp));
    dp[V] = 0;
    
    for (int k = 0; k < K; k++) {
        for (int v = 0; v <= V; v++) {
            for (int i = 0; i < M; i++) {
                int product = magic[i][0];
                int cost = 0;
                for (int j = 1; magic[i][j]; j++) {
                    cost += sell[magic[i][j]];
                }
                if (v >= cost) {
                    dp[v - cost + buy[product]] = max(dp[v - cost + buy[product]], dp[v] + buy[product] - cost);
                }
            }
        }
    }
    
    int ans = 0;
    for (int v = 0; v <= V; v++) {
        ans = max(ans, dp[v]);
    }
    
    printf("%d\n", ans);
    
    return 0;
}