#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 10007

typedef struct Edge {
    int v, next;
} Edge;

Edge edges[100010];
int head[100010], cnt;

void addEdge(int u, int v) {
    edges[cnt].v = v;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int n, k;
int subtreeSize[100010], dp[100010][160], totalSize[100010][160];

void dfs(int u, int parent) {
    subtreeSize[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        if (v != parent) {
            dfs(v, u);
            subtreeSize[u] += subtreeSize[v];
        }
    }
    
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k; j++) {
            if (i + j <= k) {
                dp[u][i + j] = (dp[u][i + j] + dp[u][i] * totalSize[v][j] % MOD) % MOD;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &k);
    memset(head, -1, sizeof(head));
    
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    
    dfs(1, 0);
    
    for (int i = 1; i <= n; i++) {
        printf("%d\n", dp[i][k]);
    }
    
    return 0;
}