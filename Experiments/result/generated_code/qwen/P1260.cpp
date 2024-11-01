#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 5000

int n, m;
int T[MAX_N];
int graph[MAX_N][MAX_N];
int in_degree[MAX_N];

void initialize() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
        in_degree[i] = 0;
        T[i] = -1;
    }
}

void add_edge(int u, int v, int b) {
    graph[u-1][v-1] = b;
    in_degree[v-1]++;
}

int topological_sort() {
    int count = 0;
    int queue[MAX_N];
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front != rear) {
        int u = queue[front++];
        T[u] = count;
        count++;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }

    return count == n ? 1 : 0;
}

int check_solution() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != 0 && T[i] + graph[i][j] > T[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d %d", &n, &m);
    initialize();

    for (int i = 0; i < m; i++) {
        int u, v, b;
        scanf("%d %d %d", &u, &v, &b);
        add_edge(u, v, b);
    }

    if (!topological_sort()) {
        printf("NO SOLUTION\n");
        return 0;
    }

    if (!check_solution()) {
        printf("NO SOLUTION\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", T[i]);
    }

    return 0;
}