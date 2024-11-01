#include <stdio.h>
#include <string.h>

#define MAXN 26

int n, m;
int graph[MAXN][MAXN];
int in_degree[MAXN];
int visited[MAXN];

int topological_sort() {
    int in_degree_copy[MAXN];
    memcpy(in_degree_copy, in_degree, sizeof(in_degree));
    int count = 0;
    int order[MAXN];
    int found = 0;

    for (int i = 0; i < n; i++) {
        int zero_in_degree = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && in_degree_copy[j] == 0) {
                if (zero_in_degree != -1) {
                    return 0; // More than one node with zero in-degree, cannot determine order
                }
                zero_in_degree = j;
            }
        }
        if (zero_in_degree == -1) {
            return -1; // Cycle detected, inconsistency found
        }
        order[count++] = zero_in_degree;
        visited[zero_in_degree] = 1;
        for (int j = 0; j < n; j++) {
            if (graph[zero_in_degree][j]) {
                in_degree_copy[j]--;
            }
        }
    }
    return 1; // Successfully determined order
}

int main() {
    scanf("%d %d", &n, &m);
    memset(graph, 0, sizeof(graph));
    memset(in_degree, 0, sizeof(in_degree));
    memset(visited, 0, sizeof(visited));

    int determined = 0;
    int inconsistency = 0;
    int relations = 0;

    for (int i = 0; i < m; i++) {
        char a, b, op;
        scanf(" %c%c%c", &a, &op, &b);
        int u = a - 'A';
        int v = b - 'A';
        if (!graph[u][v]) {
            graph[u][v] = 1;
            in_degree[v]++;
        }
        relations++;

        int result = topological_sort();
        if (result == 1) {
            determined = relations;
            printf("Sorted sequence determined after %d relations: ", determined);
            for (int j = 0; j < n; j++) {
                printf("%c", order[j] + 'A');
            }
            printf(".\n");
            return 0;
        } else if (result == -1) {
            inconsistency = relations;
            printf("Inconsistency found after %d relations.\n", inconsistency);
            return 0;
        }
    }

    printf("Sorted sequence cannot be determined.\n");
    return 0;
}