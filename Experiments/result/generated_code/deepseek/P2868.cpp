#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>

#define MAXN 1005
#define MAXM 5005
#define EPS 1e-6

typedef struct {
    int to, next;
    double weight;
} Edge;

Edge edges[MAXM];
int head[MAXN], cnt;
double dist[MAXN];
int fun[MAXN];
int n, m;

void add_edge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

bool bellman_ford(double mid) {
    for (int i = 1; i <= n; i++) dist[i] = -DBL_MAX;
    dist[1] = 0;
    bool updated;
    for (int i = 0; i < n; i++) {
        updated = false;
        for (int u = 1; u <= n; u++) {
            if (dist[u] == -DBL_MAX) continue;
            for (int j = head[u]; j != -1; j = edges[j].next) {
                int v = edges[j].to;
                double new_dist = dist[u] + (fun[u] - mid * edges[j].weight);
                if (new_dist > dist[v]) {
                    dist[v] = new_dist;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }
    return updated;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &fun[i]);
        head[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    double left = 0, right = 1000;
    while (right - left > EPS) {
        double mid = (left + right) / 2;
        if (bellman_ford(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    printf("%.2f\n", left);
    return 0;
}