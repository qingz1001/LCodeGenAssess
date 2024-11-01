#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 5005
#define INF 1e9

int n, m;
int dist[MAXN];
int edges[MAXN][3];

bool bellman_ford() {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[1] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            int type = edges[j][0];
            int a = edges[j][1];
            int b = edges[j][2];
            int c = edges[j][3];

            if (type == 1) {
                if (dist[a] > dist[b] - c) {
                    dist[a] = dist[b] - c;
                }
            } else if (type == 2) {
                if (dist[a] < dist[b] + c) {
                    dist[a] = dist[b] + c;
                }
            } else if (type == 3) {
                if (dist[a] != dist[b]) {
                    dist[a] = dist[b];
                }
            }
        }
    }

    for (int j = 0; j < m; j++) {
        int type = edges[j][0];
        int a = edges[j][1];
        int b = edges[j][2];
        int c = edges[j][3];

        if (type == 1 && dist[a] > dist[b] - c) {
            return false;
        }
        if (type == 2 && dist[a] < dist[b] + c) {
            return false;
        }
        if (type == 3 && dist[a] != dist[b]) {
            return false;
        }
    }

    return true;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int type, a, b, c;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d %d %d", &a, &b, &c);
            edges[i][0] = 1;
            edges[i][1] = a;
            edges[i][2] = b;
            edges[i][3] = -c;
        } else if (type == 2) {
            scanf("%d %d %d", &a, &b, &c);
            edges[i][0] = 2;
            edges[i][1] = a;
            edges[i][2] = b;
            edges[i][3] = c;
        } else if (type == 3) {
            scanf("%d %d", &a, &b);
            edges[i][0] = 3;
            edges[i][1] = a;
            edges[i][2] = b;
            edges[i][3] = 0;
        }
    }

    if (bellman_ford()) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}