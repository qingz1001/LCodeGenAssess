#include <stdio.h>
#include <stdlib.h>

#define MAX_N 105

int n, p;
int C[MAX_N], U[MAX_N];
int adj[MAX_N][MAX_N];
int in_degree[MAX_N];

void initialize() {
    for (int i = 0; i < n; ++i) {
        C[i] = 0;
        U[i] = 0;
        for (int j = 0; j < n; ++j) {
            adj[i][j] = 0;
        }
        in_degree[i] = 0;
    }
}

void read_input() {
    scanf("%d %d", &n, &p);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &C[i], &U[i]);
    }
    for (int i = 0; i < p; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u - 1][v - 1] = w;
        in_degree[v - 1]++;
    }
}

void topological_sort() {
    int queue[MAX_N];
    int front = 0, rear = 0;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front != rear) {
        int u = queue[front++];
        if (C[u] > U[u]) {
            for (int v = 0; v < n; ++v) {
                if (adj[u][v] != 0) {
                    C[v] += C[u] * adj[u][v];
                    in_degree[v]--;
                    if (in_degree[v] == 0) {
                        queue[rear++] = v;
                    }
                }
            }
        }
    }
}

void print_output() {
    int found = 0;
    for (int i = 0; i < n; ++i) {
        if (i >= n - p && C[i] > 0) {
            printf("%d %d\n", i + 1, C[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("NULL\n");
    }
}

int main() {
    initialize();
    read_input();
    topological_sort();
    print_output();
    return 0;
}