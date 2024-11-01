#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 200005

typedef struct {
    int to, weight;
} Edge;

typedef struct {
    int idx, type, amount;
} Order;

int n, m, q;
int order_seq[MAXN];
int order_amount[MAXN];
Edge edges[MAXM];
int head[MAXN];
int next_edge[MAXM];
int train_stations[MAXN];
int dist[MAXN];

void add_edge(int u, int v, int w, int idx) {
    edges[idx].to = v;
    edges[idx].weight = w;
    next_edge[idx] = head[u];
    head[u] = idx;
}

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) dist[i] = INT_MAX;
    dist[start] = 0;
    int queue[MAXN];
    int front = 0, rear = 0;
    queue[rear++] = start;

    while (front != rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = next_edge[i]) {
            int v = edges[i].to;
            int w = edges[i].weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &order_seq[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &order_amount[i]);
    }
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w, i * 2);
        add_edge(v, u, w, i * 2 + 1);
    }
    for (int i = 0; i < q; i++) {
        scanf("%d", &train_stations[i]);
    }

    int current_city = order_seq[1];
    int current_gold = 0;

    for (int i = 1; i <= n; i++) {
        int next_city = order_seq[i];
        dijkstra(current_city);
        int min_weight = INT_MAX;
        for (int j = 0; j < q; j++) {
            if (dist[train_stations[j]] < min_weight) {
                min_weight = dist[train_stations[j]];
            }
        }
        if (order_amount[next_city] < 0) {
            int sell_amount = -order_amount[next_city];
            if (current_gold > sell_amount) {
                printf("%d\n", sell_amount);
                current_gold -= sell_amount;
            } else {
                printf("%d\n", current_gold);
                current_gold = 0;
            }
        } else {
            int buy_amount = order_amount[next_city];
            if (current_gold + buy_amount <= min_weight) {
                current_gold += buy_amount;
            } else {
                current_gold = min_weight;
            }
        }
        current_city = next_city;
    }

    return 0;
}