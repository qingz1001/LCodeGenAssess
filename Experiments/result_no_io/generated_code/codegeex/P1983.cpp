#include <stdio.h>

int n, m;
int stations[1001];
int level[1001];
int graph[1001][1001];
int in_degree[1001];

void topological_sort() {
    int stack[1001], top = 0;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            stack[top++] = i;
        }
    }
    int count = 0;
    while (top > 0) {
        int u = stack[--top];
        level[u] = count++;
        for (int v = 1; v <= n; v++) {
            if (graph[u][v] && in_degree[v] == 0) {
                stack[top++] = v;
                in_degree[v]--;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int s;
        scanf("%d", &s);
        for (int j = 0; j < s; j++) {
            scanf("%d", &stations[j]);
        }
        for (int j = 0; j < s - 1; j++) {
            for (int k = j + 1; k < s; k++) {
                graph[stations[j]][stations[k]] = 1;
                in_degree[stations[k]]++;
            }
        }
    }
    topological_sort();
    int max_level = 0;
    for (int i = 1; i <= n; i++) {
        if (level[i] > max_level) {
            max_level = level[i];
        }
    }
    printf("%d\n", max_level + 1);
    return 0;
}