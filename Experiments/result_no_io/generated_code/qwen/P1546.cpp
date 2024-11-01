#include <stdio.h>
#include <limits.h>

#define MAX_N 100

int min(int a, int b) {
    return (a < b) ? a : b;
}

void primMST(int graph[MAX_N][MAX_N], int V) {
    int parent[MAX_N]; // Array to store constructed MST
    int key[MAX_N];   // Key values used to pick minimum weight edge in cut
    int mstSet[MAX_N]; // To represent set of vertices included in MST

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;     // Start with the first vertex
    parent[0] = -1; // First node is always root of MST

    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        mstSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    int sum = 0;
    for (int i = 1; i < V; i++) {
        sum += graph[i][parent[i]];
    }
    printf("%d\n", sum);
}

int main() {
    int N;
    scanf("%d", &N);

    int graph[MAX_N][MAX_N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph, N);

    return 0;
}