#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50000
#define MAXM 50000

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
char materials[MAXN + 1];
char eigen_string[MAXM + 1];
int N, M;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int popularity(char *P, int L) {
    int count = 0;
    for (int i = 0; i <= M - L; i++) {
        if (strncmp(eigen_string + i, P, L) == 0) {
            count++;
        }
    }
    return count;
}

void dfs(int u, int parent, char *path, int depth, int *total_popularity) {
    path[depth] = materials[u - 1];
    path[depth + 1] = '\0';
    *total_popularity += popularity(path, depth + 1);

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != parent) {
            dfs(v, u, path, depth + 1, total_popularity);
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    memset(head, -1, sizeof(head));

    for (int i = 0; i < N - 1; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }

    scanf("%s", materials);
    scanf("%s", eigen_string);

    int total_popularity = 0;
    char path[MAXN + 1];

    for (int i = 1; i <= N; i++) {
        dfs(i, -1, path, 0, &total_popularity);
    }

    int result = (total_popularity * N * N) / (N * N);
    printf("%d\n", result);

    return 0;
}