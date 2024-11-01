#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

typedef struct {
    int type;
    int a, b, v;
    int t;
} Event;

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count;

Event events[MAXM];
int n, m;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void init() {
    memset(head, -1, sizeof(head));
    edge_count = 0;
}

int main() {
    scanf("%d %d", &n, &m);
    init();

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 0; i < m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 0) {
            int a, b, v;
            scanf("%d %d %d", &a, &b, &v);
            events[i].type = type;
            events[i].a = a;
            events[i].b = b;
            events[i].v = v;
        } else if (type == 1) {
            int t;
            scanf("%d", &t);
            events[i].type = type;
            events[i].t = t;
        } else if (type == 2) {
            int x;
            scanf("%d", &x);
            events[i].type = type;
            events[i].a = x;
        }
    }

    // Process events
    for (int i = 0; i < m; i++) {
        if (events[i].type == 2) {
            int x = events[i].a;
            // Find the maximum importance of requests not affected by the failure of server x
            // This part needs to be implemented based on the tree structure and the requests
            // For simplicity, we assume a function `find_max_importance` is implemented
            int max_importance = find_max_importance(x);
            printf("%d\n", max_importance);
        }
    }

    return 0;
}

int find_max_importance(int x) {
    // This function should be implemented based on the tree structure and the requests
    // For now, it returns -1 as a placeholder
    return -1;
}