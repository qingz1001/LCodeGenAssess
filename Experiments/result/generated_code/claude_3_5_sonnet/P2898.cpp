#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 1000001
#define MAX_Q 25001

typedef struct {
    int l, r, x;
} Query;

int n, q;
Query queries[MAX_Q];
int tree[MAX_N * 4];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = INT_MAX;
        return;
    }
    int mid = (start + end) / 2;
    build(node*2, start, mid);
    build(node*2+1, mid+1, end);
    tree[node] = INT_MAX;
}

void update(int node, int start, int end, int l, int r, int val) {
    if (l > end || r < start) return;
    if (l <= start && end <= r) {
        tree[node] = val < tree[node] ? val : tree[node];
        return;
    }
    int mid = (start + end) / 2;
    update(node*2, start, mid, l, r, val);
    update(node*2+1, mid+1, end, l, r, val);
}

int query(int node, int start, int end, int l, int r) {
    if (l > end || r < start) return INT_MAX;
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    int left = query(node*2, start, mid, l, r);
    int right = query(node*2+1, mid+1, end, l, r);
    return left < right ? left : right;
}

int main() {
    scanf("%d %d", &n, &q);
    
    for (int i = 1; i <= q; i++) {
        scanf("%d %d %d", &queries[i].l, &queries[i].r, &queries[i].x);
    }
    
    build(1, 1, n);
    
    for (int i = 1; i <= q; i++) {
        int min_val = query(1, 1, n, queries[i].l, queries[i].r);
        if (min_val < queries[i].x) {
            printf("%d\n", i);
            return 0;
        }
        update(1, 1, n, queries[i].l, queries[i].r, queries[i].x);
    }
    
    printf("0\n");
    return 0;
}