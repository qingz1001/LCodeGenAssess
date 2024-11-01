#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 20001

typedef struct {
    int a, b, Ti, ti;
} Edge;

Edge edges[MAX_M];
int parent[MAX_N];
int n, k, m;

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->ti - ((Edge*)b)->ti;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

int check(int mid) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    
    int count = 0;
    int self_think = 0;
    
    for (int i = 0; i < m; i++) {
        if (edges[i].ti > mid) break;
        
        if (find(edges[i].a) != find(edges[i].b)) {
            unite(edges[i].a, edges[i].b);
            count++;
        }
    }
    
    for (int i = 0; i < m && count < n - 1; i++) {
        if (edges[i].Ti <= mid && find(edges[i].a) != find(edges[i].b)) {
            unite(edges[i].a, edges[i].b);
            count++;
            self_think++;
        }
    }
    
    return count == n - 1 && self_think >= k;
}

int main() {
    scanf("%d %d %d", &n, &k, &m);
    
    int max_time = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &edges[i].a, &edges[i].b, &edges[i].Ti, &edges[i].ti);
        if (edges[i].ti > max_time) max_time = edges[i].ti;
        if (edges[i].Ti > max_time) max_time = edges[i].Ti;
    }
    
    qsort(edges, m, sizeof(Edge), cmp);
    
    int left = 0, right = max_time, mid;
    while (left < right) {
        mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    printf("%d\n", left);
    
    return 0;
}