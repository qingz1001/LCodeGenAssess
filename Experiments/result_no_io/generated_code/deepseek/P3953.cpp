#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 200005
#define MOD 1000000007

typedef struct {
    int to, next, weight;
} Edge;

Edge edges[MAXM];
int head[MAXN], edge_count;
int dist[MAXN], dp[MAXN][55];
int visited[MAXN], in_queue[MAXN];
int N, M, K, P;

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void spfa(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(in_queue, 0, sizeof(in_queue));
    dist[start] = 0;
    int queue[MAXN], front = 0, rear = 0;
    queue[rear++] = start;
    in_queue[start] = 1;

    while (front != rear) {
        int u = queue[front++];
        if (front == MAXN) front = 0;
        in_queue[u] = 0;

        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            int w = edges[i].weight;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!in_queue[v]) {
                    queue[rear++] = v;
                    if (rear == MAXN) rear = 0;
                    in_queue[v] = 1;
                }
            }
        }
    }
}

int dfs(int u, int k) {
    if (dp[u][k] != -1) return dp[u][k];
    if (u == N) return 1;

    int res = 0;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        int w = edges[i].weight;
        int new_k = k - (dist[v] + w - dist[u]);
        if (new_k >= 0) {
            res = (res + dfs(v, new_k)) % P;
        }
    }
    dp[u][k] = res;
    return res;
}

int solve() {
    spfa(1);
    if (dist[N] == INT_MAX) return -1;

    memset(dp, -1, sizeof(dp));
    int ans = 0;
    for (int k = 0; k <= K; k++) {
        ans = (ans + dfs(1, k)) % P;
    }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d %d", &N, &M, &K, &P);
        memset(head, -1, sizeof(head));
        edge_count = 0;

        for (int i = 0; i < M; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            add_edge(u, v, w);
        }

        int result = solve();
        printf("%d\n", result);
    }
    return 0;
}