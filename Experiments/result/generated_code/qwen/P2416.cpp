#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 200005

int N, M;
int graph[MAXN][MAXN];
int visited[MAXN];

void dfs(int node, int parent) {
    visited[node] = 1;
    for (int i = 1; i <= N; i++) {
        if (graph[node][i] && i != parent) {
            dfs(i, node);
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int X, Y, Z;
        scanf("%d %d %d", &X, &Y, &Z);
        graph[X][Y] = graph[Y][X] = Z;
    }

    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int S, T;
        scanf("%d %d", &S, &T);

        for (int i = 1; i <= N; i++) {
            visited[i] = 0;
        }

        dfs(S, -1);
        if (visited[T]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}