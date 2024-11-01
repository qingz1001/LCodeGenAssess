#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5005
#define MAXK 1005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_cnt = 0;
int pos[MAXK], eat_count[MAXK];
int n, k, h;

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void dfs(int u, int p, int target, int *path, int *path_len) {
    path[(*path_len)++] = u;
    if (u == target) return;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == p) continue;
        dfs(v, u, target, path, path_len);
        if (path[*path_len - 1] == target) return;
    }
    (*path_len)--;
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &pos[i]);
        eat_count[i] = 0;
    }
    scanf("%d", &h);
    for (int i = 0; i < h; i++) {
        int food_pos;
        scanf("%d", &food_pos);
        int path[MAXN], path_len = 0;
        for (int j = 0; j < k; j++) {
            path_len = 0;
            dfs(pos[j], -1, food_pos, path, &path_len);
            int stop = 0;
            for (int l = 0; l < path_len - 1; l++) {
                for (int m = 0; m < k; m++) {
                    if (m != j && pos[m] == path[l]) {
                        stop = 1;
                        break;
                    }
                }
                if (stop) break;
            }
            if (!stop && path[path_len - 1] == food_pos) {
                pos[j] = food_pos;
                eat_count[j]++;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        printf("%d %d\n", pos[i], eat_count[i]);
    }
    return 0;
}