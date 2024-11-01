#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 301
#define MAX_S 1001
#define INF 0x3f3f3f3f

int n, s;
int graph[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
int diameter[MAX_N];
int diameter_len;

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

void find_diameter() {
    int max_dist = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dist[i][j] > max_dist) {
                max_dist = dist[i][j];
                diameter_len = 0;
                for (int k = 1; k <= n; k++) {
                    if (dist[i][k] + dist[k][j] == dist[i][j]) {
                        diameter[diameter_len++] = k;
                    }
                }
            }
        }
    }
}

int min_eccentric_distance() {
    int min_ecc = INF;
    for (int i = 0; i < diameter_len; i++) {
        for (int j = i; j < diameter_len && dist[diameter[i]][diameter[j]] <= s; j++) {
            int max_dist = 0;
            for (int k = 1; k <= n; k++) {
                int min_dist = INF;
                for (int l = i; l <= j; l++) {
                    if (dist[k][diameter[l]] < min_dist) {
                        min_dist = dist[k][diameter[l]];
                    }
                }
                if (min_dist > max_dist) {
                    max_dist = min_dist;
                }
            }
            if (max_dist < min_ecc) {
                min_ecc = max_dist;
            }
        }
    }
    return min_ecc;
}

int main() {
    scanf("%d %d", &n, &s);
    
    memset(graph, 0x3f, sizeof(graph));
    memset(dist, 0x3f, sizeof(dist));
    
    for (int i = 1; i <= n; i++) {
        graph[i][i] = dist[i][i] = 0;
    }
    
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w;
        dist[u][v] = dist[v][u] = w;
    }
    
    floyd();
    find_diameter();
    int result = min_eccentric_distance();
    
    printf("%d\n", result);
    
    return 0;
}