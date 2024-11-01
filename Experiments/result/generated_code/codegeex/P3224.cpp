#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001

int n, m, q;
int parent[MAXN], rank[MAXN], islands[MAXN];

// 初始化并查集
void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// 查找集合的根节点
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 合并两个集合
void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// 读取输入
int read() {
    int x;
    scanf("%d", &x);
    return x;
}

// 处理查询操作
void processQuery(int x, int k) {
    int rootX = find(x);
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (find(i) == rootX) {
            count++;
            if (count == k) {
                printf("%d\n", islands[i]);
                return;
            }
        }
    }
    printf("-1\n");
}

int main() {
    n = read();
    m = read();
    init(n);
    for (int i = 1; i <= n; i++) {
        islands[i] = read();
    }
    for (int i = 1; i <= m; i++) {
        int u = read();
        int v = read();
        unite(u, v);
    }
    q = read();
    for (int i = 0; i < q; i++) {
        char op;
        scanf(" %c", &op);
        int x = read();
        int y = read();
        if (op == 'Q') {
            processQuery(x, y);
        } else if (op == 'B') {
            unite(x, y);
        }
    }
    return 0;
}