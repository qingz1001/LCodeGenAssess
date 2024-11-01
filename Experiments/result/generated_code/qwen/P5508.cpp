#include <stdio.h>
#include <stdlib.h>

#define INF 1e9

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int v[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }

    int groups[m][5];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d %d", &groups[i][0], &groups[i][1], &groups[i][2], &groups[i][3], &groups[i][4]);
    }

    // Initialize distance array with infinity
    long long dist[n + 1];
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[1] = 0;

    // Process each group of tunnels
    for (int i = 0; i < m; i++) {
        int s_l = groups[i][0], s_r = groups[i][1], t_l = groups[i][2], t_r = groups[i][3], w = groups[i][4];
        for (int j = s_l; j <= s_r; j++) {
            for (int k = t_l; k <= t_r; k++) {
                if (dist[j] != INF) {
                    dist[k] = dist[j] + w;
                }
            }
        }
    }

    // Check if there is a path to the nth cave
    if (dist[n] == INF) {
        printf("-1\n");
        return 0;
    }

    // Backtrack to find the path
    int path[n];
    int path_len = 0;
    int current = n;
    while (current != 1) {
        path[path_len++] = current;
        for (int j = 1; j <= n; j++) {
            if (dist[current] - dist[j] == abs(current - j) * v[j]) {
                current = j;
                break;
            }
        }
    }
    path[path_len++] = 1;

    // Print the result
    printf("%lld\n", dist[n]);
    printf("%d\n", path_len);
    for (int i = path_len - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");

    return 0;
}