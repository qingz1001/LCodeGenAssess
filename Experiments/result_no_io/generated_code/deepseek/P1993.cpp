#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5005
#define INF 0x3f3f3f3f

int n, m;
int dist[MAXN];
int edges[MAXN][3];

int bellman_ford() {
    memset(dist, INF, sizeof(dist));
    dist[1] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            int a = edges[j][0], b = edges[j][1], c = edges[j][2];
            if (dist[a] + c < dist[b]) {
                dist[b] = dist[a] + c;
            }
        }
    }

    for (int j = 0; j < m; j++) {
        int a = edges[j][0], b = edges[j][1], c = edges[j][2];
        if (dist[a] + c < dist[b]) {
            return 0; // Negative cycle detected
        }
    }

    return 1; // No negative cycle
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int type, a, b, c;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d %d %d", &a, &b, &c);
            edges[i][0] = a;
            edges[i][1] = b;
            edges[i][2] = -c;
        } else if (type == 2) {
            scanf("%d %d %d", &a, &b, &c);
            edges[i][0] = b;
            edges[i][1] = a;
            edges[i][2] = c;
        } else if (type == 3) {
            scanf("%d %d", &a, &b);
            edges[i][0] = a;
            edges[i][1] = b;
            edges[i][2] = 0;
            edges[m + i][0] = b;
            edges[m + i][1] = a;
            edges[m + i][2] = 0;
        }
    }

    if (bellman_ford()) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}