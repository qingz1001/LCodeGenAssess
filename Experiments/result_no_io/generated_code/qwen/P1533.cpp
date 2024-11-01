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
        tree[node] = tree[node * 2] > tree[node * 2 + 1] ? tree[node * 2] : tree[node * 2 + 1];
    }
}

int query(int node, int start, int end, int left, int right) {
    if (left > end || right < start) {
        return -1; // Return invalid value to indicate no valid element found
    }
    if (start >= left && end <= right) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    int q1 = query(node * 2, start, mid, left, right);
    int q2 = query(node * 2 + 1, mid + 1, end, left, right);
    if (q1 == -1) return q2;
    if (q2 == -1) return q1;
    return q1 > q2 ? q1 : q2;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    build(1, 1, n);

    for (int i = 0; i < m; ++i) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        int result = -1;
        int lo = 1, hi = r - l + 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int pos = query(1, 1, n, l, l + mid - 1);
            if (pos != -1) {
                result = pos;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        printf("%d\n", result);
    }

    return 0;
}