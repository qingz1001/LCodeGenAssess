#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005
#define MAXM 1005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN << 1];
int head[MAXN], edgeCount;
int depth[MAXN], parent[MAXN][20];

void addEdge(int u, int v) {
    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dfs(int node, int prev) {
    depth[node] = depth[prev] + 1;
    parent[node][0] = prev;
    for (int i = 1; i <= 19; ++i) {
        parent[node][i] = parent[parent[node][i - 1]][i - 1];
    }
    for (int e = head[node]; e != -1; e = edges[e].next) {
        int neighbor = edges[e].to;
        if (neighbor == prev) continue;
        dfs(neighbor, node);
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    int diff = depth[v] - depth[u];
    for (int i = 0; diff; ++i) {
        if (diff & 1) {
            v = parent[v][i];
        }
        diff >>= 1;
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

int countRepeats(const char *path, const char *pattern, int pathLength, int patternLength) {
    int count = 0;
    for (int i = 0; i <= pathLength - patternLength; ++i) {
        if (strncmp(path + i, pattern, patternLength) == 0) {
            count++;
            i += patternLength - 1;
        }
    }
    return count;
}

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        int n, m;
        scanf("%d %d", &n, &m);
        char nodes[n + 1];
        scanf("%s", nodes);
        memset(head, -1, sizeof(head));
        edgeCount = 0;
        for (int i = 1; i < n; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        dfs(1, 0);

        char S[MAXM];
        scanf("%s", S);

        int result = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                int lcaNode = lca(i, j);
                int pathLength = depth[i] + depth[j] - 2 * depth[lcaNode];
                int patternLength = m;
                int repeatedCount = countRepeats(nodes + i - 1, S, pathLength, patternLength);
                result += repeatedCount;
            }
        }

        printf("%d\n", result);
    }
    return 0;
}