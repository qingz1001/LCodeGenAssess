#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 50001
#define MOD 10000

struct Edge {
    int to, time;
    struct Edge* next;
};

struct Edge* graph[MAX_N];
long long dp[MAX_N];
int n, m, s, t, t0;

void addEdge(int from, int to, int time) {
    struct Edge* e = (struct Edge*)malloc(sizeof(struct Edge));
    e->to = to;
    e->time = time;
    e->next = graph[from];
    graph[from] = e;
}

long long dfs(int u) {
    if (u == t) return 1;
    if (dp[u] != -1) return dp[u];
    
    dp[u] = 0;
    for (struct Edge* e = graph[u]; e; e = e->next) {
        dp[u] = (dp[u] + dfs(e->to)) % MOD;
    }
    return dp[u];
}

long long calculateTotalTime(int u) {
    if (u == t) return 0;
    
    long long total = 0;
    for (struct Edge* e = graph[u]; e; e = e->next) {
        total = (total + (calculateTotalTime(e->to) + e->time) * dfs(e->to)) % MOD;
    }
    return total;
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &t0);
    
    for (int i = 0; i < m; i++) {
        int x, y, time;
        scanf("%d %d %d", &x, &y, &time);
        addEdge(x, y, time);
    }
    
    memset(dp, -1, sizeof(dp));
    long long paths = dfs(s);
    long long totalTime = calculateTotalTime(s);
    long long result = (totalTime + (paths - 1) * t0) % MOD;
    
    printf("%lld\n", result);
    
    return 0;
}