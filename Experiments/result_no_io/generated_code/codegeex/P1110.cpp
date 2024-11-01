#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500005

int a[MAXN << 2];
int n, m;

void build(int node, int start, int end) {
    if (start == end) {
        scanf("%d", &a[node]);
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        a[node] = abs(a[2 * node] - a[2 * node + 1]);
    }
}

void insert(int node, int start, int end, int idx, int value) {
    if (start == end) {
        a[node] = value;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            insert(2 * node, start, mid, idx, value);
        } else {
            insert(2 * node + 1, mid + 1, end, idx, value);
        }
        a[node] = abs(a[2 * node] - a[2 * node + 1]);
    }
}

int query_min_gap(int node, int start, int end) {
    if (start == end) {
        return INT_MAX;
    } else {
        int mid = (start + end) / 2;
        return (a[node] == INT_MAX) ? INT_MAX : a[node];
    }
}

int query_min_sort_gap(int node, int start, int end) {
    if (start == end) {
        return INT_MAX;
    } else {
        int mid = (start + end) / 2;
        return (a[node] == INT_MAX) ? INT_MIN : a[node];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    build(1, 1, n);
    int min_sort_gap = query_min_sort_gap(1, 1, n);
    char op[20];
    for (int i = 0; i < m; i++) {
        scanf("%s", op);
        if (op[0] == 'I') {
            int idx, k;
            scanf("%d %d", &idx, &k);
            insert(1, 1, n, idx, k);
            if (idx > 1) {
                min_sort_gap = (min_sort_gap < abs(a[1] - a[2])) ? min_sort_gap : abs(a[1] - a[2]);
            }
        } else if (op[4] == 'G') {
            printf("%d\n", query_min_gap(1, 1, n));
        } else if (op[4] == 'S') {
            printf("%d\n", min_sort_gap);
        }
    }
    return 0;
}