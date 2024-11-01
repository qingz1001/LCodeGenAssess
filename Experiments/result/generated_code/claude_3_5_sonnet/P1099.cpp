#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 301
#define INF 0x3f3f3f3f

int n, s;
int graph[MAXN][MAXN];
int dist[MAXN][MAXN];
int diameter = 0, center = 0;
int diameter_path[MAXN], path_len = 0;

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
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dist[i][j] > diameter) {
                diameter = dist[i][j];
                center = (i + j) / 2;
            }
        }
    }
}

void construct_diameter_path(int start, int end, int cur) {
    if (start == end) {
        diameter_path[cur] = start;
        path_len = cur + 1;
        return;
    }
    diameter_path[cur] = start;
    for (int i = 1; i <= n; i++) {
        if (graph[start][i] && dist[start][end] == graph[start][i] + dist[i][end]) {
            construct_diameter_path(i, end, cur + 1);
            break;
        }
    }
}

int calculate_ecc(int start, int end) {
    int max_dist = 0;
    for (int i = 1; i <= n; i++) {
        int min_dist = INF;
        for (int j = start; j <= end; j++) {
            if (dist[i][diameter_path[j]] < min_dist) {
                min_dist = dist[i][diameter_path[j]];
            }
        }
        if (min_dist > max_dist) {
            max_dist = min_dist;
        }
    }
    return max_dist;
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
    
    int start = 0, end = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dist[i][j] == diameter) {
                start = i;
                end = j;
                break;
            }
        }
        if (start) break;
    }
    
    construct_diameter_path(start, end, 0);
    
    int min_ecc = INF;
    for (int i = 0; i < path_len; i++) {
        for (int j = i; j < path_len; j++) {
            int len = 0;
            for (int k = i; k < j; k++) {
                len += graph[diameter_path[k]][diameter_path[k+1]];
            }
            if (len <= s) {
                int ecc = calculate_ecc(i, j);
                if (ecc < min_ecc) {
                    min_ecc = ecc;
                }
            }
        }
    }
    
    printf("%d\n", min_ecc);
    
    return 0;
}