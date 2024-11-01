#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005

typedef struct {
    int to, next, w;
} Edge;

Edge edges[MAXN << 1];
int head[MAXN], edgeIndex;
int n, k;

void addEdge(int from, int to, int w) {
    edges[edgeIndex].to = to;
    edges[edgeIndex].next = head[from];
    edges[edgeIndex].w = w;
    head[from] = edgeIndex++;
}

int dfs(int u, int p) {
    int maxProfit = 0, secondMaxProfit = 0;
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == p) continue;
        int profit = dfs(v, u);
        if (edges[i].w >= 0) {
            if (profit > maxProfit) {
                secondMaxProfit = maxProfit;
                maxProfit = profit + edges[i].w;
            } else if (profit > secondMaxProfit) {
                secondMaxProfit = profit + edges[i].w;
            }
        } else {
            if (-profit > maxProfit) {
                secondMaxProfit = maxProfit;
                maxProfit = -profit + edges[i].w;
            } else if (-profit > secondMaxProfit) {
                secondMaxProfit = -profit + edges[i].w;
            }
        }
    }
    return maxProfit;
}

int main() {
    scanf("%d %d", &n, &k);
    memset(head, -1, sizeof(head));
    edgeIndex = 0;
    for (int i = 0; i < n - 1; ++i) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        addEdge(x, y, w);
        addEdge(y, x, w);
    }

    int maxProfit = dfs(1, 0);
    printf("%d\n", maxProfit);

    return 0;
}