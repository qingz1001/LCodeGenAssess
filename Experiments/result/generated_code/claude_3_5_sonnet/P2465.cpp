#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_P 12
#define MAX_T 4096
#define INF 0x3f3f3f3f

int n, p, t;
int graph[MAX_N + 1][MAX_N + 1];
int cost[MAX_N + 1][MAX_P + 1];
int profit[MAX_T + 1];
int dp[MAX_N + 1][1 << MAX_P];
int parent[MAX_N + 1];

void dfs(int u, int fa) {
    parent[u] = fa;
    for (int v = 1; v <= n; v++) {
        if (v != fa && graph[u][v]) {
            dfs(v, u);
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);
    
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][y] = graph[y][x] = 1;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= p; j++) {
            scanf("%d", &cost[i][j]);
        }
    }
    
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int v, c, mask = 0;
        scanf("%d %d", &v, &c);
        for (int j = 0; j < c; j++) {
            int x;
            scanf("%d", &x);
            mask |= (1 << (x - 1));
        }
        profit[mask] += v;
    }
    
    dfs(1, 0);
    
    memset(dp, -0x3f, sizeof(dp));
    dp[1][0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int mask = 0; mask < (1 << p); mask++) {
            if (dp[i][mask] == -INF) continue;
            
            // 不在当前节点建立新的分部
            int newMask = mask;
            int cur = i;
            while (cur != 0) {
                dp[cur][newMask] = (dp[cur][newMask] > dp[i][mask] + profit[newMask]) ? 
                                   dp[cur][newMask] : dp[i][mask] + profit[newMask];
                cur = parent[cur];
            }
            
            // 在当前节点建立新的分部
            for (int j = 0; j < p; j++) {
                if ((mask & (1 << j)) == 0) {
                    newMask = mask | (1 << j);
                    int newValue = dp[i][mask] - cost[i][j + 1];
                    cur = i;
                    while (cur != 0) {
                        dp[cur][newMask] = (dp[cur][newMask] > newValue + profit[newMask]) ? 
                                           dp[cur][newMask] : newValue + profit[newMask];
                        cur = parent[cur];
                    }
                }
            }
        }
    }
    
    int maxProfit = -INF;
    for (int mask = 0; mask < (1 << p); mask++) {
        if (dp[1][mask] > maxProfit) {
            maxProfit = dp[1][mask];
        }
    }
    
    printf("%d\n", maxProfit);
    
    return 0;
}