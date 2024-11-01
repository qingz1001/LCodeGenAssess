#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005
#define INF 1e9

typedef struct {
    int to, weight;
} Edge;

int n, m;
Edge edges[MAXN];
int dist[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;

    typedef struct {
        int node, cost;
    } State;
    State pq[MAXN * 2];
    int pq_size = 0;

    void push(int node, int cost) {
        pq[pq_size++] = (State){node, cost};
        int idx = pq_size - 1;
        while (idx > 0 && pq[(idx - 1) / 2].cost > pq[idx].cost) {
            State tmp = pq[(idx - 1) / 2];
            pq[(idx - 1) / 2] = pq[idx];
            pq[idx] = tmp;
            idx = (idx - 1) / 2;
        }
    }

    State pop() {
        State ret = pq[0];
        pq[0] = pq[--pq_size];
        int idx = 0;
        while (idx * 2 + 1 < pq_size) {
            int child = idx * 2 + 1;
            if (child + 1 < pq_size && pq[child + 1].cost < pq[child].cost) {
                child++;
            }
            if (pq[idx].cost <= pq[child].cost) break;
            State tmp = pq[idx];
            pq[idx] = pq[child];
            pq[child] = tmp;
            idx = child;
        }
        return ret;
    }

    push(start, 0);
    while (pq_size > 0) {
        State state = pop();
        int node = state.node, cost = state.cost;
        if (cost > dist[node]) continue;
        for (int i = 0; i < m; ++i) {
            if (edges[i].from == node) {
                int next_node = edges[i].to, next_cost = cost + edges[i].weight;
                if (next_cost < dist[next_node]) {
                    dist[next_node] = next_cost;
                    push(next_node, next_cost);
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
    }

    dijkstra(1);

    long long total_cost = 0;
    for (int i = 1; i <= n; ++i) {
        total_cost += dist[i];
    }

    printf("%lld\n", total_cost);

    return 0;
}