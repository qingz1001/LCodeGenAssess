#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 200005

typedef struct {
    int u, v, w;
} Edge;

typedef struct {
    int parent, size, depth, max_weight;
} Node;

Edge edges[MAXM];
Node nodes[MAXN];

int find(int x) {
    if (nodes[x].parent != x) {
        nodes[x].parent = find(nodes[x].parent);
    }
    return nodes[x].parent;
}

void union_set(int x, int y) {
    x = find(x), y = find(y);
    if (nodes[x].size < nodes[y].size) {
        nodes[x].parent = y;
        nodes[y].size += nodes[x].size;
    } else {
        nodes[y].parent = x;
        nodes[x].size += nodes[y].size;
    }
}

void update_max_weight(int root, int parent, int weight) {
    if (weight > nodes[root].max_weight) {
        nodes[root].max_weight = weight;
    }
    for (int i = root + 1; i <= nodes[root].size; ++i) {
        if (nodes[i].parent == parent) {
            update_max_weight(i, root, weight);
        }
    }
}

int query_max_weight(int root, int target) {
    if (root == target) {
        return nodes[root].max_weight;
    }
    int max_weight = -1;
    for (int i = root + 1; i <= nodes[root].size; ++i) {
        if (nodes[i].parent == target) {
            max_weight = query_max_weight(i, target);
            break;
        }
    }
    return max_weight;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i) {
        nodes[i].parent = i;
        nodes[i].size = 1;
        nodes[i].depth = 0;
        nodes[i].max_weight = -1;
    }

    for (int i = 0; i < n - 1; ++i) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
        union_set(edges[i].u, edges[i].v);
    }

    for (int i = 0; i < m; ++i) {
        int type;
        scanf("%d", &type);
        if (type == 0) {
            int a, b, v;
            scanf("%d %d %d", &a, &b, &v);
            int root_a = find(a), root_b = find(b);
            if (root_a == root_b) {
                continue;
            }
            union_set(root_a, root_b);
            update_max_weight(root_a, root_b, v);
        } else if (type == 1) {
            // Ignore end request event
        } else if (type == 2) {
            int x;
            scanf("%d", &x);
            int root_x = find(x);
            printf("%d\n", query_max_weight(root_x, x));
        }
    }

    return 0;
}