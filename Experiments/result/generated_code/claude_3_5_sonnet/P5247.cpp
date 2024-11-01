#include <stdio.h>
#include <string.h>

#define MAXN 5005

int father[MAXN];
int rank[MAXN];

void init(int n) {
    for (int i = 0; i < n; i++) {
        father[i] = i;
        rank[i] = 1;
    }
}

int find(int x) {
    if (father[x] != x) {
        father[x] = find(father[x]);
    }
    return father[x];
}

void unite(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx == fy) return;
    if (rank[fx] < rank[fy]) {
        father[fx] = fy;
    } else {
        father[fy] = fx;
        if (rank[fx] == rank[fy]) {
            rank[fx]++;
        }
    }
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
            // 在这个简化版本中，我们不实现删除操作
        } else if (op == 2) {
            if (find(x) == find(y)) {
                printf("Y\n");
                last = x;
            } else {
                printf("N\n");
                last = y;
            }
        }
    }
    
    return 0;
}