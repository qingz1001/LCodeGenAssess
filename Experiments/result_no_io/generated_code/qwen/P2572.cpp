#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int arr[MAXN];
int lazy[MAXN * 4];

void build(int node, int start, int end) {
    if (start == end) {
        lazy[node] = -1;
        arr[start] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        lazy[node] = -1;
    }
}

void update_range(int node, int start, int end, int l, int r, int val) {
    if (lazy[node] != -1) {
        if (lazy[node] == 0 || lazy[node] == 1) {
            arr[start] = lazy[node];
            arr[end] = lazy[node];
        } else {
            arr[start] = 1 - arr[start];
            arr[end] = 1 - arr[end];
        }
        if (start != end) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = -1;
    }

    if (r < start || end < l)
        return;

    if (l <= start && end <= r) {
        if (val == 0 || val == 1) {
            arr[start] = val;
            arr[end] = val;
        } else {
            arr[start] = 1 - arr[start];
            arr[end] = 1 - arr[end];
        }
        if (start != end) {
            lazy[node * 2] = val;
            lazy[node * 2 + 1] = val;
        }
        return;
    }

    int mid = (start + end) / 2;
    update_range(node * 2, start, mid, l, r, val);
    update_range(node * 2 + 1, mid + 1, end, l, r, val);

    arr[start] = arr[start];
    arr[end] = arr[end];
}

int query_count(int node, int start, int end, int l, int r) {
    if (lazy[node] != -1) {
        if (lazy[node] == 0 || lazy[node] == 1) {
            arr[start] = lazy[node];
            arr[end] = lazy[node];
        } else {
            arr[start] = 1 - arr[start];
            arr[end] = 1 - arr[end];
        }
        if (start != end) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = -1;
    }

    if (r < start || end < l)
        return 0;

    if (l <= start && end <= r)
        return arr[start];

    int mid = (start + end) / 2;
    int left = query_count(node * 2, start, mid, l, r);
    int right = query_count(node * 2 + 1, mid + 1, end, l, r);
    return left + right;
}

int query_max_consecutive_ones(int node, int start, int end, int l, int r) {
    if (lazy[node] != -1) {
        if (lazy[node] == 0 || lazy[node] == 1) {
            arr[start] = lazy[node];
            arr[end] = lazy[node];
        } else {
            arr[start] = 1 - arr[start];
            arr[end] = 1 - arr[end];
        }
        if (start != end) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = -1;
    }

    if (r < start || end < l)
        return 0;

    if (l <= start && end <= r) {
        int count = 0;
        for (int i = start; i <= end; i++) {
            if (arr[i] == 1)
                count++;
            else
                count = 0;
        }
        return count;
    }

    int mid = (start + end) / 2;
    int left = query_max_consecutive_ones(node * 2, start, mid, l, r);
    int right = query_max_consecutive_ones(node * 2 + 1, mid + 1, end, l, r);
    return left > right ? left : right;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    build(1, 0, n - 1);

    while (m--) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 0 || op == 1 || op == 2)
            update_range(1, 0, n - 1, l, r, op);
        else if (op == 3)
            printf("%d\n", query_count(1, 0, n - 1, l, r));
        else if (op == 4)
            printf("%d\n", query_max_consecutive_ones(1, 0, n - 1, l, r));
    }

    return 0;
}