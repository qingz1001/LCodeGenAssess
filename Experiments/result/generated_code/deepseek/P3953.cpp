#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 200005
#define MAXK 55
#define MOD 1000000007

typedef struct {
    int to, next, weight;
} Edge;

Edge edges[MAXM];
int head[MAXN], edge_count;
int dist[MAXN], dp[MAXN][MAXK];
int in_queue[MAXN], visited[MAXN][MAXK];
int N, M, K, P;

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void spfa(int start) {
    int queue[MAXN], front = 0, rear = 0;
    memset(dist, 0x3f, sizeof(dist));
    memset(in_queue, 0, sizeof(in_queue));
    dist[start] = 0;
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
    if (visited[u][k]) return -1;
    if (dp[u][k] != -1) return dp[u][k];
    visited[u][k] = 1;
    dp[u][k] = 0;

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        int w = edges[i].weight;
        int new_k = k - (dist[v] + w - dist[u]);
        if (new_k >= 0) {
            int res = dfs(v, new_k);
            if (res == -1) return -1;
            dp[u][k] = (dp[u][k] + res) % P;
        }
    }

    visited[u][k] = 0;
    if (u == N && k == 0) dp[u][k] = 1;
    return dp[u][k];
}

int solve() {
    scanf("%d %d %d %d", &N, &M, &K, &P);
    memset(head, -1, sizeof(head));
    edge_count = 0;

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    spfa(1);

    memset(dp, -1, sizeof(dp));
    memset(visited, 0, sizeof(visited));

    int result = 0;
    for (int i = 0; i <= K; i++) {
        int res = dfs(1, i);
        if (res == -1) return -1;
        result = (result + res) % P;
    }

    return result;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int result = solve();
        printf("%d\n", result);
    }
    return 0;
}