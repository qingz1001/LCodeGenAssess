#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 10005
#define MAXM 100005

typedef struct {
    int v;
    int next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
int color[MAXN];
bool impossible = false;

void add_edge(int u, int v) {
    edges[edge_count].v = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u, int c) {
    color[u] = c;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        if (color[v] == -1) {
            dfs(v, 1 - c);
        } else if (color[v] == c) {
            impossible = true;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        color[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    int total_crabs = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            int count[2] = {0, 0};
            dfs(i, 0);
            for (int j = 1; j <= n; j++) {
                if (color[j] != -1) {
                    count[color[j]]++;
                    color[j] = -1;
                }
            }
            total_crabs += (count[0] < count[1] ? count[0] : count[1]);
        }
    }

    if (impossible) {
        printf("Impossible\n");
    } else {
        printf("%d\n", total_crabs);
    }

    return 0;
}