#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 99

typedef struct {
    int to;
    int next;
} Edge;

int head[MAX_N + 1], cnt;
Edge edges[2 * MAX_N];
int w[MAX_N + 1], c[MAX_N + 1];
int n, m;
double dp[MAX_N + 1][MAX_M + 1][2];

void addEdge(int u, int v) {
    edges[++cnt].to = v;
    edges[cnt].next = head[u];
    head[u] = cnt;
}

void dfs(int u, int fa) {
    dp[u][0][0] = w[u];
    dp[u][0][1] = c[u];
    
    for (int i = head[u]; i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == fa) continue;
        
        dfs(v, u);
        
        for (int j = m; j >= 0; j--) {
            for (int k = 0; k <= j; k++) {
                if (dp[u][j-k][0] + dp[v][k][0] > 0 && dp[u][j-k][1] + dp[v][k][1] > 0) {
                    double tmp = (dp[u][j-k][0] + dp[v][k][0]) / (dp[u][j-k][1] + dp[v][k][1]);
                    if (tmp > dp[u][j][0] / dp[u][j][1] || dp[u][j][1] == 0) {
                        dp[u][j][0] = dp[u][j-k][0] + dp[v][k][0];
                        dp[u][j][1] = dp[u][j-k][1] + dp[v][k][1];
                    }
                }
            }
        }
    }
    
    for (int j = m; j > 0; j--) {
        if (dp[u][j-1][0] / dp[u][j-1][1] > dp[u][j][0] / dp[u][j][1] || dp[u][j][1] == 0) {
            dp[u][j][0] = dp[u][j-1][0];
            dp[u][j][1] = dp[u][j-1][1];
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
    }
    
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    
    dfs(1, 0);
    
    printf("%.1f\n", dp[1][m][0] / dp[1][m][1]);
    
    return 0;
}