#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20001
#define INF 0x3f3f3f3f

struct Edge {
    int to, weight;
    struct Edge* next;
};

struct Edge* graph[MAX_N];
int n, initial_strength;
int dp[MAX_N][2];  // dp[i][0]: 不在i处放置放大器, dp[i][1]: 在i处放置放大器

void add_edge(int u, int v, int w) {
    struct Edge* e = (struct Edge*)malloc(sizeof(struct Edge));
    e->to = v;
    e->weight = w;
    e->next = graph[u];
    graph[u] = e;
}

void dfs(int u, int parent) {
    int child_sum0 = 0, child_sum1 = 0;
    struct Edge* e;
    
    for (e = graph[u]; e; e = e->next) {
        int v = e->to;
        if (v == parent) continue;
        
        dfs(v, u);
        
        if (dp[v][0] - e->weight > 0) {
            child_sum0 += dp[v][0] - e->weight;
        }
        if (dp[v][1] - e->weight > 0) {
            child_sum0 += dp[v][1] - e->weight;
        }
        child_sum1 += dp[v][1] < dp[v][0] ? dp[v][1] : dp[v][0];
    }
    
    dp[u][0] = child_sum0;
    dp[u][1] = child_sum1 + 1;
}

int main() {
    int i, k, v, w;
    scanf("%d", &n);
    
    for (i = 1; i <= n; i++) {
        scanf("%d", &k);
        while (k--) {
            scanf("%d %d", &v, &w);
            add_edge(i, v, w);
            add_edge(v, i, w);
        }
    }
    
    scanf("%d", &initial_strength);
    
    dfs(1, 0);
    
    int result = dp[1][1] < dp[1][0] ? dp[1][1] : dp[1][0];
    
    if (result <= initial_strength) {
        printf("%d\n", result);
    } else {
        printf("No solution.\n");
    }
    
    return 0;
}