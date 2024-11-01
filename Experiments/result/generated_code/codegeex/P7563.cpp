#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAXN 200005

typedef struct {
    int to, next;
    long long cost;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], cnt;
long long dp[MAXN], inDegree[MAXN];
int n;

void addEdge(int u, int v, long long cost) {
    edges[cnt].to = v;
    edges[cnt].cost = cost;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u) {
    if (dp[u] != LLONG_MAX) {
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            dp[v] = (dp[v] == LLONG_MAX) ? dp[u] + edges[i].cost : dp[v] < dp[u] + edges[i].cost ? dp[v] : dp[u] + edges[i].cost;
            inDegree[v]--;
            if (inDegree[v] == 0) {
                dfs(v);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        dp[i] = LLONG_MAX;
        inDegree[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        int a, h;
        long long c;
        scanf("%d %d %lld", &a, &h, &c);
        addEdge(a, i, c);
        inDegree[i]++;
    }
    dp[1] = 0;
    dfs(1);
    long long result = LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        result = result < dp[i] ? result : dp[i];
    }
    printf("%lld\n", result);
    return 0;
}