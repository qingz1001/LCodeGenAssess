#include <stdio.h>
#include <string.h>

#define MAXN 26
#define MAXM 601

int n, m;
int indegree[MAXN]; // 存储每个节点的入度
int adj[MAXN][MAXN]; // 存储邻接矩阵
int visited[MAXN]; // 记录节点是否已访问

void dfs(int u) {
    visited[u] = 1;
    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(indegree, 0, sizeof(indegree));
    memset(adj, 0, sizeof(adj));
    memset(visited, 0, sizeof(visited));

    int x = 0;
    for (int i = 0; i < m; i++) {
        char a, b, c;
        scanf(" %c%*c%c", &a, &c);
        int u = a - 'A';
        int v = c - 'A';
        adj[u][v] = 1;
        indegree[v]++;
        x = i + 1;

        int sorted = 1;
        for (int j = 0; j < n; j++) {
            if (indegree[j] == 0) {
                sorted = 0;
                break;
            }
        }

        if (sorted) {
            printf("Sorted sequence determined after %d relations: ", x);
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (indegree[j] == 0) {
                    dfs(j);
                    break;
                }
            }
            for (int j = 0; j < n; j++) {
                if (visited[j]) {
                    printf("%c", 'A' + j);
                    count++;
                }
            }
            printf(".\n");
            return 0;
        }
    }

    if (x == m) {
        printf("Sorted sequence cannot be determined.\n");
    } else {
        printf("Inconsistency found after %d relations.\n", x);
    }

    return 0;
}