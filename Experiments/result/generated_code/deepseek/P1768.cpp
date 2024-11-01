#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#define MAXN 7000
#define MAXM 20000

typedef struct {
    int to, next;
    int V, P;
} Edge;

Edge edges[MAXM + 1];
int head[MAXN + 1], cnt = 0;

void addEdge(int u, int v, int V, int P) {
    edges[cnt].to = v;
    edges[cnt].V = V;
    edges[cnt].P = P;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

double maxRatio = -1.0;
int visited[MAXN + 1];
double ratio[MAXN + 1];

void dfs(int u, double currentRatio) {
    if (visited[u]) {
        if (currentRatio > ratio[u]) {
            maxRatio = currentRatio;
        }
        return;
    }

    visited[u] = 1;
    ratio[u] = currentRatio;

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        double newRatio = currentRatio * (double)edges[i].V / edges[i].P;
        dfs(v, newRatio);
    }

    visited[u] = 0;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        head[i] = -1;
    }

    for (int i = 0; i < M; i++) {
        int u, v, V, P;
        scanf("%d %d %d %d", &u, &v, &V, &P);
        addEdge(u, v, V, P);
    }

    for (int i = 1; i <= N; i++) {
        dfs(i, 1.0);
    }

    if (maxRatio == -1.0) {
        printf("-1\n");
    } else {
        printf("%.1f\n", maxRatio);
    }

    return 0;
}