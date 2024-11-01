#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001

typedef struct {
    int next;
    int to;
    int color;
} Edge;

Edge edges[MAXN << 1];
int head[MAXN], edge_count = 0;

void add_edge(int u, int v, int c) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    edges[edge_count].color = c;
    head[u] = edge_count++;
}

int n;
int count[MAXN][2];

void dfs(int u, int p, int sum) {
    count[sum][edges[u].color]++;
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to, c = edges[i].color;
        if (v != p) {
            dfs(v, u, sum ^ (1 << c));
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        add_edge(u, v, c);
        add_edge(v, u, c);
    }

    long long result = 0;
    for (int i = 1; i <= n; i++) {
        memset(count, 0, sizeof(count));
        dfs(i, -1, 0);
        for (int j = 0; j < 2; j++) {
            result += (long long)count[j][0] * count[j][1];
        }
    }

    printf("%lld\n", result);

    return 0;
}