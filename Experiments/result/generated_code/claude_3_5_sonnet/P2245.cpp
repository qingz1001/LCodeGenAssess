#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 300005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, weight;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
int parent[MAX_N];
int rank[MAX_N];
int max_danger[MAX_N][MAX_N];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
        memset(max_danger[i], 0x3f, sizeof(max_danger[i]));
        max_danger[i][i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

void add_edge(int u, int v, int w) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->weight = w;
    e->next = graph[u];
    graph[u] = e;
}

int main() {
    int n, m, q;
    scanf("%d %d", &n, &m);
    
    init(n);
    
    for (int i = 0; i < m; i++) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        add_edge(a, b, l);
        add_edge(b, a, l);
        unite(a, b);
        if (max_danger[a][b] > l) {
            max_danger[a][b] = max_danger[b][a] = l;
        }
    }
    
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int max_ik = max_danger[i][k];
                int max_kj = max_danger[k][j];
                int max_path = (max_ik > max_kj) ? max_ik : max_kj;
                if (max_danger[i][j] > max_path) {
                    max_danger[i][j] = max_path;
                }
            }
        }
    }
    
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (find(a) != find(b)) {
            printf("impossible\n");
        } else {
            printf("%d\n", max_danger[a][b]);
        }
    }
    
    return 0;
}