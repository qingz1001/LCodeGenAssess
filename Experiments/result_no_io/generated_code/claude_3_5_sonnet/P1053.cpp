#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50001

int n;
int wish[MAXN][2];
int visited[MAXN];
int group[MAXN];
int group_size;

void dfs(int u) {
    visited[u] = 1;
    group[group_size++] = u;
    for (int i = 0; i < 2; i++) {
        int v = wish[u][i];
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &wish[i][0], &wish[i][1]);
    }

    int total_cost = 0;
    memset(visited, 0, sizeof(visited));

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            group_size = 0;
            dfs(i);

            if (group_size == 2) {
                total_cost += 2;
            } else if (group_size > 2) {
                total_cost += group_size;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int a = wish[i][0], b = wish[i][1];
        if (wish[a][0] != i && wish[a][1] != i) {
            printf("-1\n");
            return 0;
        }
        if (wish[b][0] != i && wish[b][1] != i) {
            printf("-1\n");
            return 0;
        }
    }

    printf("%d\n", total_cost);
    return 0;
}