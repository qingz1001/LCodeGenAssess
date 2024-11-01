#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 10005
#define MAXM 100005

typedef struct {
    int v;
    int next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
int color[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].v = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

bool dfs(int u, int c) {
    color[u] = c;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        if (color[v] == c) return false;
        if (color[v] == 0 && !dfs(v, 3 - c)) return false;
    }
    return true;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        color[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    int count = 0;
    bool possible = true;

    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            if (!dfs(i, 1)) {
                possible = false;
                break;
            }
        }
    }

    if (!possible) {
        printf("Impossible\n");
    } else {
        int color1 = 0, color2 = 0;
        for (int i = 1; i <= n; i++) {
            if (color[i] == 1) color1++;
            else if (color[i] == 2) color2++;
        }
        printf("%d\n", color1 < color2 ? color1 : color2);
    }

    return 0;
}