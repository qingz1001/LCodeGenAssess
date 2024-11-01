#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 2005
#define MAXM 10005

int n, m;
int k[MAXN];
int graph[MAXN][MAXN];
int in_degree[MAXN];
int earliest[MAXN];

void topological_sort(int *result) {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int idx = 0;
    while (front < rear) {
        int u = queue[front++];
        result[idx++] = u;
        for (int v = 1; v <= n; v++) {
            if (graph[u][v]) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &k[i]);
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
        in_degree[b]++;
    }

    int result[MAXN];
    topological_sort(result);

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    for (int i = 1; i <= n; i++) {
        earliest[i] = 1;
        for (int j = 1; j <= n; j++) {
            if (graph[j][i]) {
                earliest[i] = earliest[j] + 1;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", earliest[i]);
    }
    printf("\n");

    return 0;
}