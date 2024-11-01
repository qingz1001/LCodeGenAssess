#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 301
#define INF INT_MAX

int n, s;
int adj[MAXN][MAXN];
int dist[MAXN];
int visited[MAXN];

void add_edge(int u, int v, int w) {
    adj[u][v] = w;
    adj[v][u] = w;
}

void dfs(int node, int parent, int d) {
    dist[node] = d;
    visited[node] = 1;
    for (int i = 1; i <= n; i++) {
        if (adj[node][i] > 0 && i != parent && !visited[i]) {
            dfs(i, node, d + adj[node][i]);
        }
    }
}

int find_farthest_node() {
    int farthest_node = 1;
    int max_distance = 0;
    memset(dist, 0, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    dfs(1, -1, 0);
    for (int i = 1; i <= n; i++) {
        if (dist[i] > max_distance) {
            max_distance = dist[i];
            farthest_node = i;
        }
    }
    return farthest_node;
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    int farthest_node = find_farthest_node();
    memset(dist, 0, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    dfs(farthest_node, -1, 0);

    int diameter_end = 1;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > dist[diameter_end]) {
            diameter_end = i;
        }
    }

    int min_eccentricity = INF;
    for (int i = 1; i <= n; i++) {
        if (dist[i] <= s) {
            memset(dist, 0, sizeof(dist));
            memset(visited, 0, sizeof(visited));
            dfs(i, -1, 0);
            int max_eccentricity = 0;
            for (int j = 1; j <= n; j++) {
                if (dist[j] > max_eccentricity) {
                    max_eccentricity = dist[j];
                }
            }
            if (max_eccentricity < min_eccentricity) {
                min_eccentricity = max_eccentricity;
            }
        }
    }

    printf("%d\n", min_eccentricity);
    return 0;
}