#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define INF 0x3f3f3f3f

int N;
int price[MAX_N];
int dp[MAX_N];
long long cnt[MAX_N];
int graph[MAX_N][MAX_N];

void dfs(int u) {
    if (dp[u] != INF) return;
    
    dp[u] = price[u];
    cnt[u] = 1;
    
    for (int v = 0; v < N; v++) {
        if (graph[u][v]) {
            int w = graph[u][v] - 1;
            dfs(v);
            dfs(w);
            int new_cost = dp[v] + dp[w];
            if (new_cost < dp[u]) {
                dp[u] = new_cost;
                cnt[u] = cnt[v] * cnt[w];
            } else if (new_cost == dp[u]) {
                cnt[u] += cnt[v] * cnt[w];
            }
        }
    }
}

int main() {
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &price[i]);
    }
    
    memset(graph, 0, sizeof(graph));
    int a, b, c;
    while (scanf("%d %d %d", &a, &b, &c) == 3) {
        graph[c][a] = b + 1;
    }
    
    memset(dp, 0x3f, sizeof(dp));
    memset(cnt, 0, sizeof(cnt));
    
    dfs(0);
    
    printf("%d %lld\n", dp[0], cnt[0]);
    
    return 0;
}