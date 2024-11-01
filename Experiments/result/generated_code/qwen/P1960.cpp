#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define MAX_M 100000

int n, m;
int graph[MAX_N + 1][MAX_N + 1];
int indegree[MAX_N + 1];
int rank[MAX_N + 1];

void topological_sort() {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            rank[count++] = i;
        }
    }
    while (count > 0) {
        int u = rank[count - 1];
        count--;
        for (int v = 1; v <= n; v++) {
            if (graph[u][v]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    rank[count++] = v;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
        indegree[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][y] = 1;
        indegree[y]++;
    }
    topological_sort();
    if (count != n) {
        printf("0\n");
        return 0;
    }
    int has_other_rank = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if ((graph[rank[i]][rank[j]] && !graph[rank[j]][rank[i]]) || (!graph[rank[i]][rank[j]] && graph[rank[j]][rank[i]])) {
                continue;
            } else {
                has_other_rank = 1;
                break;
            }
        }
        if (has_other_rank) break;
    }
    if (has_other_rank) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    for (int i = 0; i < n; i++) {
        printf("%d\n", rank[i]);
    }
    return 0;
}