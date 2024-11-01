#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005
#define MAXM 50005

int n, m;
int a[MAXN];
int tree[MAXN * 4];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = a[start];
    } else {
        int mid = (start + end) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        tree[node] = fmin(tree[node * 2], tree[node * 2 + 1]);
    }
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return INT_MAX;
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    int p1 = query(node * 2, start, mid, l, r);
    int p2 = query(node * 2 + 1, mid + 1, end, l, r);
    return fmin(p1, p2);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    build(1, 1, n);

    for (int i = 1; i <= m; i++) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        int result = INT_MAX;
        for (int j = 0; j < k; j++) {
            int min_val = query(1, 1, n, l + j, r - j);
            if (min_val != INT_MAX) {
                result = fmin(result, min_val);
            }
        }
        printf("%d\n", result);
    }

    return 0;
}