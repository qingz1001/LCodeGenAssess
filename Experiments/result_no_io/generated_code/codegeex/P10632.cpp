#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30010

int n;
int g[MAXN][MAXN];
int size[MAXN], maxSubSize[MAXN], centroid[MAXN], par[MAXN];
bool visited[MAXN];

void dfs(int u, int p) {
    size[u] = 1;
    maxSubSize[u] = 0;
    for (int i = 0; i < n; i++) {
        if (g[u][i] && i != p) {
            dfs(i, u);
            size[u] += size[i];
            maxSubSize[u] = (maxSubSize[u] < size[i]) ? size[i] : maxSubSize[u];
        }
    }
    maxSubSize[u] = (maxSubSize[u] < n - size[u]) ? n - size[u] : maxSubSize[u];
    if (maxSubSize[u] < maxSubSize[centroid[n]]) {
        centroid[n] = u;
    }
}

void findCentroid(int u, int p) {
    for (int i = 0; i < n; i++) {
        if (g[u][i] && i != p && size[i] > n / 2) {
            centroid[i] = centroid[n];
            findCentroid(i, u);
        }
    }
}

void calculateTime(int u, double *totalTime, int *count) {
    if (visited[u]) return;
    visited[u] = true;
    (*totalTime) += size[u];
    (*count)++;
    for (int i = 0; i < n; i++) {
        if (g[u][i] && !visited[i]) {
            calculateTime(i, totalTime, count);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a][b] = g[b][a] = 1;
    }

    centroid[n] = MAXN;
    dfs(0, -1);
    centroid[0] = centroid[n];
    findCentroid(0, -1);

    int centroidNode = centroid[0];
    memset(visited, 0, sizeof(visited));
    double totalTime = 0;
    int count = 0;
    calculateTime(centroidNode, &totalTime, &count);

    printf("%.4f\n", totalTime / count);
    return 0;
}