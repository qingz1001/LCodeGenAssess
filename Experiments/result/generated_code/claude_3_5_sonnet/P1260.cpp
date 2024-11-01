#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1001
#define MAX_M 5001

int n, m;
int dist[MAX_N];
int edge[MAX_M][3];

int bellman_ford() {
    memset(dist, 0x3f, sizeof(dist));
    dist[0] = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = edge[j][0], v = edge[j][1], w = edge[j][2];
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (i == n - 1) return 0;
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        edge[i][0] = v;
        edge[i][1] = u;
        edge[i][2] = w;
    }
    
    for (int i = 0; i < n; i++) {
        edge[m+i][0] = n;
        edge[m+i][1] = i;
        edge[m+i][2] = 0;
    }
    m += n;
    n++;
    
    if (!bellman_ford()) {
        printf("NO SOLUTION\n");
    } else {
        int min_dist = INT_MAX;
        for (int i = 0; i < n-1; i++) {
            if (dist[i] < min_dist) {
                min_dist = dist[i];
            }
        }
        for (int i = 0; i < n-1; i++) {
            printf("%d\n", dist[i] - min_dist);
        }
    }
    
    return 0;
}