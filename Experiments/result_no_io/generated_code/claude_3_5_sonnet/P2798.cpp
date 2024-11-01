#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 20001

struct Edge {
    int u, v, t, T;
};

struct Edge edges[MAX_M];
int parent[MAX_N];
int n, k, m;

int cmp(const void *a, const void *b) {
    return ((struct Edge*)a)->T - ((struct Edge*)b)->T;
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
    
    int count = 0, self_thought = 0;
    
    for (int i = 0; i < m; i++) {
        if (edges[i].T <= mid) {
            if (find(edges[i].u) != find(edges[i].v)) {
                unite(edges[i].u, edges[i].v);
                count++;
                self_thought++;
            }
        } else if (edges[i].t <= mid) {
            if (find(edges[i].u) != find(edges[i].v)) {
                unite(edges[i].u, edges[i].v);
                count++;
            }
        }
    }
    
    return count == n - 1 && self_thought >= k;
}

int main() {
    scanf("%d %d %d", &n, &k, &m);
    
    int max_T = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].T, &edges[i].t);
        if (edges[i].T > max_T) max_T = edges[i].T;
    }
    
    qsort(edges, m, sizeof(struct Edge), cmp);
    
    int left = 1, right = max_T, ans = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    printf("%d\n", ans);
    
    return 0;
}