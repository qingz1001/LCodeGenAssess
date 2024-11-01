#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 128
#define INF INT_MAX

int dist[MAXN];
char bessie[MAXN];
int G[MAXN][MAXN];
int n;

void dijkstra(int start) {
    bool visited[MAXN];
    memset(visited, false, sizeof(visited));
    dist[start] = 0;
    visited[start] = true;

    for (int i = 0; i < n; i++) {
        int u = -1, min = INF;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && G[u][v] != INF && dist[u] + G[u][v] < dist[v]) {
                dist[v] = dist[u] + G[u][v];
            }
        }
    }
}

int main() {
    int m;
    scanf("%d", &m);
    memset(G, 0x3f, sizeof(G)); // Initialize graph with INF
    memset(dist, 0x3f, sizeof(dist)); // Initialize distances with INF

    for (int i = 0; i < m; i++) {
        char a, b;
        int d;
        scanf(" %c %c %d", &a, &b, &d);
        int u = a - 'A';
        int v = b - 'A';
        if (b == 'Z') v = 26;
        if (a == 'Z') u = 26;
        G[u][v] = G[v][u] = d;
    }

    n = 27; // There are 26 letters and 1 more for the barn (Z)

    dijkstra(26); // Start from the barn

    int min_dist = INF;
    int min_bessie = -1;
    for (int i = 0; i < 26; i++) {
        if (dist[i] < min_dist) {
            min_dist = dist[i];
            min_bessie = i;
        }
    }

    printf("%c %d\n", min_bessie + 'A', min_dist);

    return 0;
}