#include <stdio.h>
#include <stdlib.h>

#define MAXN 105
#define MAXM 1005
#define INF 0x3f3f3f3f

typedef struct {
    int a, b, c;
} Brewery;

typedef struct {
    int d;
} Storage;

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_cnt = 0;

void add_edge(int from, int to) {
    edges[edge_cnt].to = to;
    edges[edge_cnt].next = head[from];
    head[from] = edge_cnt++;
}

double min(double a, double b) {
    return a < b ? a : b;
}

double solve(int n, int m, Brewery breweries[], Storage storages[], int channels[][MAXM]) {
    for (int i = 1; i <= n; ++i) {
        if (breweries[i - 1].a == 0) {
            add_edge(0, i);
            add_edge(i, 0);
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (channels[i - 1][j - 1]) {
                add_edge(i, n + j);
                add_edge(n + j, i);
            }
        }
    }

    for (int i = 1; i <= m; ++i) {
        add_edge(n + i, 2 * n + i);
        add_edge(2 * n + i, n + i);
    }

    double flow[n + m + 2][n + m + 2];
    for (int i = 0; i <= n + m + 1; ++i) {
        for (int j = 0; j <= n + m + 1; ++j) {
            flow[i][j] = 0.0;
        }
    }

    double cost[n + m + 2][n + m + 2];
    for (int i = 0; i <= n + m + 1; ++i) {
        for (int j = 0; j <= n + m + 1; ++j) {
            cost[i][j] = 0.0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cost[0][i] = 0.0;
        cost[i][0] = 0.0;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cost[i][n + j] = -((double)breweries[i - 1].a * (storages[j - 1].d / (double)breweries[i - 1].c));
            cost[n + j][i] = -cost[i][n + j];
        }
    }

    for (int i = 1; i <= m; ++i) {
        cost[n + i][2 * n + i] = 0.0;
        cost[2 * n + i][n + i] = 0.0;
    }

    double max_flow = 0.0;
    double total_cost = 0.0;

    while (1) {
        int dist[n + m + 2];
        bool in_queue[n + m + 2];
        int prev[n + m + 2];

        for (int i = 0; i <= n + m + 1; ++i) {
            dist[i] = INF;
            in_queue[i] = false;
            prev[i] = -1;
        }

        dist[0] = 0;
        in_queue[0] = true;

        while (1) {
            int u = -1;
            for (int i = 0; i <= n + m + 1; ++i) {
                if (!in_queue[i] && (u == -1 || dist[u] > dist[i])) {
                    u = i;
                }
            }

            if (u == -1) break;

            in_queue[u] = false;

            for (int e = head[u]; ~e; e = edges[e].next) {
                int v = edges[e].to;
                if (flow[u][v] < (double)storages[v - n - 1].d && dist[v] > dist[u] + cost[u][v]) {
                    dist[v] = dist[u] + cost[u][v];
                    prev[v] = u;
                    in_queue[v] = true;
                }
            }
        }

        if (prev[n + m + 1] == -1) break;

        double path_flow = INF;
        for (int v = n + m + 1; v != 0; v = prev[v]) {
            path_flow = min(path_flow, (double)storages[v - n - 1].d - flow[prev[v]][v]);
        }

        for (int v = n + m + 1; v != 0; v = prev[v]) {
            int u = prev[v];
            flow[u][v] += path_flow;
            flow[v][u] -= path_flow;
            total_cost += path_flow * cost[u][v];
        }

        max_flow += path_flow;
    }

    return total_cost;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Brewery breweries[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &breweries[i].a, &breweries[i].b, &breweries[i].c);
    }

    Storage storages[m];
    for (int i = 0; i < m; ++i) {
        scanf("%d", &storages[i].d);
    }

    int channels[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &channels[i][j]);
        }
    }

    double total_cost = solve(n, m, breweries, storages, channels);

    printf("%d\n", (int)total_cost);
    printf("0/1\n");

    return 0;
}