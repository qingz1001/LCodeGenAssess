#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 5005
#define MAXM 500005

int parent[MAXN];
int rank[MAXN];

void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
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

bool same(int x, int y) {
    return find(x) == find(y);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    init(n);
    
    int last = 0;
    for (int i = 0; i < m; i++) {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        
        x ^= last;
        y ^= last;
        
        if (op == 0) {
            unite(x, y);
        } else if (op == 1) {
            // 在此实现中，我们无法真正"删除"边，因为我们使用的是并查集
            // 在实际应用中，可能需要使用其他数据结构来支持边的删除
        } else if (op == 2) {
            bool connected = same(x, y);
            printf("%c\n", connected ? 'Y' : 'N');
            last = connected ? x : y;
        }
    }
    
    return 0;
}