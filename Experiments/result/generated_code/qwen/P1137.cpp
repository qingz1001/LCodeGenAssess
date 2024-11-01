#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100001

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // Adjacency list for the graph
    int *adj[MAX_N] = {NULL};
    int degree[MAX_N] = {0};

    for (int i = 0; i < M; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x] = realloc(adj[x], sizeof(int) * (degree[x] + 2));
        adj[y] = realloc(adj[y], sizeof(int) * (degree[y] + 2));
        adj[x][degree[x]++] = y;
        adj[y][degree[y]++] = x;
    }

    // Array to store the result
    int result[N];
    for (int i = 0; i < N; ++i) {
        result[i] = 0;
    }

    // BFS to find the longest path starting from each city
    for (int start = 1; start <= N; ++start) {
        int queue[MAX_N];
        int front = 0, rear = 0;
        queue[rear++] = start;

        while (front != rear) {
            int current = queue[front++];
            for (int j = 0; j < degree[current]; ++j) {
                int neighbor = adj[current][j];
                if (neighbor > current && result[start] < result[neighbor] + 1) {
                    result[start] = result[neighbor] + 1;
                    queue[rear++] = neighbor;
                }
            }
        }
    }

    // Output the results
    for (int i = 0; i < N; ++i) {
        printf("%d\n", result[i]);
    }

    return 0;
}