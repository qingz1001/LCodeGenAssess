#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300
#define INF INT_MAX

typedef struct {
    int to, weight;
} Edge;

Edge edges[MAXN][MAXN];
int edge_count[MAXN];
int dist[MAXN];
int parent[MAXN];
int diameter_path[MAXN];
int path_length;
int n, s;

void add_edge(int u, int v, int w) {
    edges[u][edge_count[u]].to = v;
    edges[u][edge_count[u]].weight = w;
    edge_count[u]++;
    edges[v][edge_count[v]].to = u;
    edges[v][edge_count[v]].weight = w;
    edge_count[v]++;
}

void dfs(int node, int par, int d) {
    dist[node] = d;
    parent[node] = par;
    for (int i = 0; i < edge_count[node]; i++) {
        int to = edges[node][i].to;
        int weight = edges[node][i].weight;
        if (to != par) {
            dfs(to, node, d + weight);
        }
    }
}

int find_farthest(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dfs(start, -1, 0);
    int farthest = start;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > dist[farthest]) {
            farthest = i;
        }
    }
    return farthest;
}

void find_diameter() {
    int u = find_farthest(1);
    int v = find_farthest(u);
    path_length = 0;
    for (int i = v; i != -1; i = parent[i]) {
        diameter_path[path_length++] = i;
    }
}

int calculate_eccentricity(int start, int end) {
    int max_dist = 0;
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dfs(start, -1, 0);
    for (int i = 1; i <= n; i++) {
        if (dist[i] > max_dist) {
            max_dist = dist[i];
        }
    }
    return max_dist;
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    find_diameter();

    int min_eccentricity = INF;
    for (int i = 0; i < path_length; i++) {
        for (int j = i; j < path_length; j++) {
            int path_sum = 0;
            for (int k = i; k < j; k++) {
                path_sum += edges[diameter_path[k]][diameter_path[k + 1]].weight;
            }
            if (path_sum <= s) {
                int eccentricity = 0;
                for (int k = 0; k < path_length; k++) {
                    int d = INF;
                    for (int l = i; l <= j; l++) {
                        d = (d < dist[diameter_path[l]]) ? d : dist[diameter_path[l]];
                    }
                    eccentricity = (eccentricity > d) ? eccentricity : d;
                }
                min_eccentricity = (min_eccentricity < eccentricity) ? min_eccentricity : eccentricity;
            }
        }
    }

    printf("%d\n", min_eccentricity);
    return 0;
}