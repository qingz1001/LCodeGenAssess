#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 301
#define INF 1000000000

int n;
int W[MAXN];
int P[MAXN][MAXN];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int find_min_vertex(int dist[], int mstSet[]) {
    int min = INF, min_index;

    for (int v = 0; v < n; v++)
        if (mstSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

int primMST() {
    int parent[MAXN]; // Array to store constructed MST
    int dist[MAXN];   // Value of shortest distance from src to i
    int mstSet[MAXN]; // To represent set of vertices not yet included in MST

    for (int i = 0; i < n; i++)
        dist[i] = INF, mstSet[i] = 0;

    dist[0] = 0;
    parent[0] = -1; // First node is always the root of

    for (int count = 0; count < n - 1; count++) {
        int u = find_min_vertex(dist, mstSet);

        mstSet[u] = 1;

        for (int v = 0; v < n; v++)
            if (P[u][v] && mstSet[v] == 0 && P[u][v] < dist[v])
                parent[v] = u, dist[v] = P[u][v];
    }

    int total_cost = 0;
    for (int i = 1; i < n; i++)
        total_cost += dist[i];

    for (int i = 0; i < n; i++)
        total_cost += W[i];

    return total_cost;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &W[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &P[i][j]);

    printf("%d\n", primMST());

    return 0;
}