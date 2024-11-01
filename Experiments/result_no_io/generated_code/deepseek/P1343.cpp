#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAXN 205
#define MAXM 2005

int n, m, x;
int capacity[MAXN][MAXN];
int dist[MAXN];
bool visited[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

void dijkstra() {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[1] = INT_MAX;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INT_MAX) break;
        visited[u] = true;

        for (int v = 1; v <= n; v++) {
            if (capacity[u][v] > 0) {
                dist[v] = min(dist[v], min(dist[u], capacity[u][v]));
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &x);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        capacity[a][b] = c;
    }

    dijkstra();

    if (dist[n] == INT_MAX) {
        printf("Orz Ni Jinan Saint Cow!\n");
    } else {
        int max_students_per_batch = dist[n];
        int num_batches = (x + max_students_per_batch - 1) / max_students_per_batch;
        printf("%d %d\n", max_students_per_batch, num_batches);
    }

    return 0;
}