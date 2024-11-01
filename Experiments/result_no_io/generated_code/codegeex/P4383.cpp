#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAXN = 300005;
const long long INF = 1e18;

struct Edge {
    int to, next;
    long long weight;
} edges[MAXN << 1];

int head[MAXN], edgeCount;
long long dp[MAXN][3], edgeWeights[MAXN];

void addEdge(int u, int v, long long w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dfs(int u, int parent) {
    dp[u][0] = 0;
    dp[u][1] = dp[u][2] = -INF;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        long long w = edges[i].weight;
        if (v == parent) continue;
        dfs(v, u);
        dp[u][0] += max({dp[v][0], dp[v][1], dp[v][2]});
        dp[u][1] = max(dp[u][1], dp[v][0] + w);
        dp[u][2] = max(dp[u][2], dp[v][0] + w);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    fill(head, head + n + 1, -1);
    for (int i = 1; i < n; i++) {
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
        edgeWeights[i] = w;
    }
    dfs(1, -1);
    long long result = -INF;
    for (int i = 1; i <= n; i++) {
        result = max(result, dp[i][0] + max(dp[i][1], dp[i][2]));
    }
    printf("%lld\n", result);
    return 0;
}