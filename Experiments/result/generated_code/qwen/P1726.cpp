#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005

int n, m;
int graph[MAXN][MAXN];
int visited[MAXN];

void dfs(int node, int *component) {
    if (visited[node]) return;
    visited[node] = 1;
    component[*component] = node;
    (*component)++;
    for (int i = 1; i <= n; i++) {
        if (graph[node][i] == 1 || graph[i][node] == 2) {
            dfs(i, component);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        graph[a][b] = t;
        if (t == 2) {
            graph[b][a] = t;
        }
    }

    int max_size = 0;
    int largest_component[MAXN];
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            int component[MAXN];
            int component_size = 0;
            dfs(i, component);
            if (component_size > max_size) {
                max_size = component_size;
                for (int j = 0; j < component_size; j++) {
                    largest_component[j] = component[j];
                }
            } else if (component_size == max_size) {
                for (int j = 0; j < component_size; j++) {
                    if (largest_component[j] > component[j]) {
                        for (int k = 0; k < component_size; k++) {
                            largest_component[k] = component[k];
                        }
                        break;
                    } else if (largest_component[j] < component[j]) {
                        break;
                    }
                }
            }
        }
    }

    printf("%d\n", max_size);
    for (int i = 0; i < max_size; i++) {
        printf("%d ", largest_component[i]);
    }
    printf("\n");

    return 0;
}