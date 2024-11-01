#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 50010
#define MAXM 100010

typedef long long ll;

struct Edge {
    int to;
    int next;
    ll weight;
} edges[MAXN * 2];

int head[MAXN];
int edgeCount;
int parent[MAXN];
int depth[MAXN];
ll subtreeSize[MAXN];
ll dp[MAXN][2];
ll maxEdge[MAXN];

void addEdge(int from, int to, ll weight) {
    edges[edgeCount].to = to;
    edges[edgeCount].weight = weight;
    edges[edgeCount].next = head[from];
    head[from] = edgeCount++;
}

void dfs(int node, int par) {
    parent[node] = par;
    depth[node] = depth[par] + 1;
    subtreeSize[node] = 1;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int neighbor = edges[i].to;
        if (neighbor == par) continue;
        dfs(neighbor, node);
        subtreeSize[node] += subtreeSize[neighbor];
        dp[node][0] += dp[neighbor][0] + edges[i].weight * subtreeSize[neighbor];
        dp[node][1] += dp[neighbor][1] + edges[i].weight * subtreeSize[neighbor];
    }
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int neighbor = edges[i].to;
        if (neighbor == par) continue;
        dp[node][1] = llabs(dp[node][1] - dp[neighbor][0] - edges[i].weight * subtreeSize[neighbor]);
    }
    maxEdge[node] = edges[head[node]].weight;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int neighbor = edges[i].to;
        if (neighbor == par) continue;
        if (dp[node][1] - dp[neighbor][0] - edges[i].weight * subtreeSize[neighbor] > dp[node][1]) {
            dp[node][1] = dp[node][1] - dp[neighbor][0] - edges[i].weight * subtreeSize[neighbor];
            maxEdge[node] = edges[i].weight;
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        memset(head, -1, sizeof(head));
        edgeCount = 0;
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            ll c;
            scanf("%d%d%lld", &a, &b, &c);
            addEdge(a, b, c);
            addEdge(b, a, c);
        }
        dfs(1, 0);
        ll ans = LLONG_MIN;
        for (int i = 2; i <= n; i++) {
            ans = llabs(dp[1][1] - dp[i][0] - maxEdge[i] * (n - subtreeSize[i]));
        }
        if (ans < 0) {
            printf("F\n");
        } else {
            printf("%lld\n", ans);
        }
    }
    return 0;
}