#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1000005
#define MAXM 1000005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_cnt;
char node_chars[MAXN];
char pattern[MAXM];
int n, m;

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

int dfs(int u, int parent, int depth, char *path, int path_len) {
    path[path_len++] = node_chars[u - 1];
    int count = 0;

    if (path_len >= m) {
        int valid = 1;
        for (int i = 0; i < m; i++) {
            if (path[path_len - m + i] != pattern[i]) {
                valid = 0;
                break;
            }
        }
        if (valid) count++;
    }

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != parent) {
            count += dfs(v, u, depth + 1, path, path_len);
        }
    }

    return count;
}

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        scanf("%d %d", &n, &m);
        scanf("%s", node_chars);
        memset(head, -1, sizeof(head));
        edge_cnt = 0;

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            add_edge(u, v);
            add_edge(v, u);
        }
        scanf("%s", pattern);

        int total_count = 0;
        char path[MAXN];
        for (int i = 1; i <= n; i++) {
            total_count += dfs(i, -1, 0, path, 0);
        }

        printf("%d\n", total_count);
    }
    return 0;
}