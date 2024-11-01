#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 305

typedef struct {
    int to, weight;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], cnt = 0;
int n, s;
int dist[MAXN], parent[MAXN];
int diameter_path[MAXN], path_len = 0;

void add_edge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt + 1].to = u;
    edges[cnt + 1].weight = w;
    head[u] = cnt++;
    head[v] = cnt++;
}

void dfs(int u, int p, int d) {
    dist[u] = d;
    parent[u] = p;
    for (int i = head[u]; i != -1; i = edges[i].to) {
        int v = edges[i].to;
        int w = edges[i].weight;
        if (v != p) {
            dfs(v, u, d + w);
        }
    }
}

int find_farthest(int start) {
    dfs(start, -1, 0);
    int farthest = start;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > dist[farthest]) {
            farthest = i;
        }
    }
    return farthest;
}

void find_diameter_path(int u) {
    while (u != -1) {
        diameter_path[path_len++] = u;
        u = parent[u];
    }
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    int farthest1 = find_farthest(1);
    int farthest2 = find_farthest(farthest1);
    find_diameter_path(farthest2);

    int min_ecc = INT_MAX;
    for (int i = 0; i < path_len; i++) {
        for (int j = i; j < path_len; j++) {
            if (dist[diameter_path[j]] - dist[diameter_path[i]] > s) break;
            int core_start = diameter_path[i];
            int core_end = diameter_path[j];
            int max_dist = 0;
            for (int k = 0; k < path_len; k++) {
                int v = diameter_path[k];
                int min_dist_to_core = INT_MAX;
                for (int l = i; l <= j; l++) {
                    int u = diameter_path[l];
                    min_dist_to_core = (dist[v] - dist[u] < min_dist_to_core) ? dist[v] - dist[u] : min_dist_to_core;
                }
                max_dist = (min_dist_to_core > max_dist) ? min_dist_to_core : max_dist;
            }
            min_ecc = (max_dist < min_ecc) ? max_dist : min_ecc;
        }
    }

    printf("%d\n", min_ecc);
    return 0;
}