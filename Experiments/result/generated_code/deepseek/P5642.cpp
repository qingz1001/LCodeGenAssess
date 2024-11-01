#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353
#define MAXN 300005

typedef struct {
    int u, v, w;
} Path;

Path paths[MAXN];
int parent[MAXN];
int size[MAXN];
int n, m;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (size[x] < size[y]) {
            int temp = x;
            x = y;
            y = temp;
        }
        parent[y] = x;
        size[x] += size[y];
    }
}

int compare_paths(const void *a, const void *b) {
    return ((Path *)b)->w - ((Path *)a)->w;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        size[i] = 1;
    }
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        union_sets(u, v);
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &paths[i].u, &paths[i].v, &paths[i].w);
    }
    
    qsort(paths, m, sizeof(Path), compare_paths);
    
    long long result = 0;
    
    for (int i = 0; i < m; i++) {
        int u = paths[i].u;
        int v = paths[i].v;
        int w = paths[i].w;
        
        int root_u = find(u);
        int root_v = find(v);
        
        if (root_u != root_v) {
            result = (result + (long long)w * size[root_u] * size[root_v]) % MOD;
            union_sets(u, v);
        }
    }
    
    printf("%lld\n", result);
    
    return 0;
}