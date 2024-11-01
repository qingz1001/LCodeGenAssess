#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 1e9

typedef struct {
    int to, weight;
} Edge;

int n, m;
Edge edges[MAXN * 2];
int degree[MAXN];

void add_edge(int u, int v, int w) {
    edges[m++] = (Edge){v, w};
    edges[m++] = (Edge){u, w};
    degree[u]++;
    degree[v]++;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    int total_time = 0;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 1) {
            int j = i;
            while (degree[j] > 1) {
                int min_weight = INF;
                int next = -1;
                for (int k = 0; k < m; ++k) {
                    if (edges[k].to == j) {
                        if (edges[k].weight < min_weight) {
                            min_weight = edges[k].weight;
                            next = edges[k].to;
                        }
                    }
                }
                total_time += 2 * min_weight;
                j = next;
            }
        }
    }

    printf("%d\n", total_time);

    return 0;
}