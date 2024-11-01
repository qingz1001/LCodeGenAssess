#include <stdio.h>
#include <stdbool.h>

#define MAXN 51

int n, m;
bool graph[MAXN][MAXN];
bool used[MAXN];
int path[MAXN];

void HamiltonianCycle(int pos) {
    if (pos == n) {
        if (graph[path[pos]][1]) {
            for (int i = 1; i <= n; ++i) {
                printf("%d ", path[i]);
            }
            printf("\n");
        }
        return;
    }

    for (int i = 2; i <= n; ++i) {
        if (!used[i] && graph[path[pos]][i]) {
            path[pos + 1] = i;
            used[i] = true;
            HamiltonianCycle(pos + 1);
            used[i] = false;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        graph[u][v] = true;
    }

    path[1] = 1;
    used[1] = true;
    HamiltonianCycle(1);

    return 0;
}