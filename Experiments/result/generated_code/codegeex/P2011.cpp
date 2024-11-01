#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 201
#define MAXM 200001

typedef struct {
    int to;
    int next;
    int weight;
} Edge;

Edge edges[MAXM];
int head[MAXN];
int cnt;
int n, m, k, q;
double voltage[MAXN];

void addEdge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u, double voltageSum) {
    voltage[u] = voltageSum;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        int w = edges[i].weight;
        if (voltage[v] == 0) {
            dfs(v, voltageSum + (double)w / (double)(w + edges[i ^ 1].weight));
        }
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &k, &q);
    for (int i = 0; i < k; i++) {
        int u, w;
        scanf("%d%d", &u, &w);
        addEdge(0, u, w);
        addEdge(u, 0, w);
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    dfs(0, 0);
    for (int i = 0; i < q; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        double result = voltage[u] - voltage[v];
        printf("%.2lf\n", result);
    }
    return 0;
}