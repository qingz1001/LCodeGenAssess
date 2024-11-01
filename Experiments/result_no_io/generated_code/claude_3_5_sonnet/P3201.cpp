#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 1000005

int n, m;
int color[MAXN];
int parent[MAXM];
int size[MAXM];
int segments;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        parent[x] = y;
        size[y] += size[x];
        segments--;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
    }
    
    for (int i = 1; i < MAXM; i++) {
        parent[i] = i;
        size[i] = 0;
    }
    
    segments = 0;
    for (int i = 1; i <= n; i++) {
        if (size[find(color[i])] == 0) {
            segments++;
        }
        size[find(color[i])]++;
        if (i > 1 && find(color[i]) != find(color[i-1])) {
            segments++;
        }
    }
    
    int op, x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d", &x, &y);
            if (find(x) != find(y)) {
                unite(x, y);
            }
        } else if (op == 2) {
            printf("%d\n", segments);
        }
    }
    
    return 0;
}