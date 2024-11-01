#include <stdio.h>
#include <string.h>
#define MAXN 505
#define MAXP 805
#define INF 0xFFFF

int dist[MAXP][MAXP];
int n, p, c;

void floyd() {
    for (int k = 1; k <= p; k++) {
        for (int i = 1; i <= p; i++) {
            for (int j = 1; j <= p; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int i, j, k, u, v, w;
    int cow[MAXP];
    int sum, min = INF;

    scanf("%d%d%d", &n, &p, &c);
    memset(dist, INF, sizeof(dist));

    for (i = 1; i <= n; i++) {
        scanf("%d", &cow[i]);
    }

    for (i = 1; i <= c; i++) {
        scanf("%d%d%d", &u, &v, &w);
        dist[u][v] = w;
        dist[v][u] = w;
    }

    floyd();

    for (i = 1; i <= p; i++) {
        sum = 0;
        for (j = 1; j <= n; j++) {
            sum += dist[cow[j]][i];
        }
        if (sum < min) {
            min = sum;
        }
    }

    printf("%d\n", min);
    return 0;
}