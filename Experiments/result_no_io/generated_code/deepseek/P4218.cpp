#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MAXM 50005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
char materials[MAXN];
char eigen_string[MAXM];
int N, M;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int kmp_table[MAXM];

void build_kmp_table() {
    int i = 0, j = -1;
    kmp_table[0] = -1;
    while (i < M) {
        while (j >= 0 && eigen_string[i] != eigen_string[j]) j = kmp_table[j];
        i++; j++;
        kmp_table[i] = j;
    }
}

int kmp_search(char *text, int len) {
    int i = 0, j = 0, count = 0;
    while (i < len) {
        while (j >= 0 && text[i] != eigen_string[j]) j = kmp_table[j];
        i++; j++;
        if (j == M) {
            count++;
            j = kmp_table[j];
        }
    }
    return count;
}

int dfs(int u, int parent, char *path, int depth) {
    path[depth] = materials[u - 1];
    int total_popularity = 0;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != parent) {
            total_popularity += dfs(v, u, path, depth + 1);
        }
    }
    path[depth + 1] = '\0';
    total_popularity += kmp_search(path, depth + 1);
    return total_popularity;
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

    build_kmp_table();

    char path[MAXN];
    int total_popularity = 0;
    for (int i = 1; i <= N; i++) {
        total_popularity += dfs(i, -1, path, 0);
    }

    int result = (total_popularity * N * N) / (N * N);
    printf("%d\n", result);

    return 0;
}