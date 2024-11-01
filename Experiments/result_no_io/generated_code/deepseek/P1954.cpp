#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 2005
#define MAXM 10005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], indegree[MAXN], k[MAXN], n, m, edge_count;
int result[MAXN], min_takeoff[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
    indegree[v]++;
}

bool topo_sort() {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int idx = 0;
    while (front < rear) {
        int u = queue[front++];
        result[idx++] = u;
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (--indegree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }

    return idx == n;
}

void calculate_min_takeoff() {
    int pos[MAXN];
    for (int i = 0; i < n; i++) {
        pos[result[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        min_takeoff[i] = 1;
        for (int j = head[i]; j != -1; j = edges[j].next) {
            int v = edges[j].to;
            if (pos[i] < pos[v]) {
                min_takeoff[i] = pos[v] + 1;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &k[i]);
        head[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
    }

    if (topo_sort()) {
        for (int i = 0; i < n; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");

        calculate_min_takeoff();
        for (int i = 1; i <= n; i++) {
            printf("%d ", min_takeoff[i]);
        }
        printf("\n");
    } else {
        printf("No solution\n");
    }

    return 0;
}