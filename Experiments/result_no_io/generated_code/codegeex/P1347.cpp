#include <stdio.h>
#include <string.h>
#define MAX 26

int n, m;
int indegree[MAX];
int adj[MAX][MAX];
int visited[MAX];

void dfs(int v) {
    visited[v] = 1;
    for (int i = 0; i < n; i++) {
        if (adj[v][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(indegree, 0, sizeof(indegree));
    memset(adj, 0, sizeof(adj));
    memset(visited, 0, sizeof(visited));

    int consistent = 1;
    int sorted = 0;
    int relations_processed = 0;

    for (int i = 0; i < m; i++) {
        char a, op, b;
        scanf(" %c %c %c", &a, &op, &b);

        if (op != '<') continue; // 只处理 '<' 关系

        int u = a - 'A';
        int v = b - 'A';

        adj[u][v] = 1;
        indegree[v]++;

        relations_processed++;

        int count_visited = 0;
        memset(visited, 0, sizeof(visited));

        for (int j = 0; j < n; j++) {
            if (!visited[j] && indegree[j] == 0) {
                dfs(j);
                count_visited++;
            }
        }

        if (count_visited > 1) {
            consistent = 0;
            break;
        }

        if (count_visited == 1) {
            sorted = 1;
            break;
        }
    }

    if (sorted) {
        printf("Sorted sequence determined after %d relations: ", relations_processed);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (indegree[j] == 0) {
                    printf("%c", j + 'A');
                    indegree[j] = -1;
                    break;
                }
            }
        }
        printf(".\n");
    } else if (!consistent) {
        printf("Inconsistency found after %d relations.\n", relations_processed);
    } else {
        printf("Sorted sequence cannot be determined.\n");
    }

    return 0;
}