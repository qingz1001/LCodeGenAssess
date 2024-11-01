#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 200005

typedef long long ll;

ll arr[MAX_M];
ll segtree[4 * MAX_M];
int last_query_result = 0;
int arr_size = 0;

void build_segtree(int node, int start, int end) {
    if (start == end) {
        segtree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build_segtree(2 * node, start, mid);
        build_segtree(2 * node + 1, mid + 1, end);
        segtree[node] = (segtree[2 * node] > segtree[2 * node + 1]) ? segtree[2 * node] : segtree[2 * node + 1];
    }
}

ll query_segtree(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return -1;
    }
    if (l <= start && end <= r) {
        return segtree[node];
    }
    int mid = (start + end) / 2;
    ll left_max = query_segtree(2 * node, start, mid, l, r);
    ll right_max = query_segtree(2 * node + 1, mid + 1, end, l, r);
    return (left_max > right_max) ? left_max : right_max;
}

void update_segtree(int node, int start, int end, int idx, ll val) {
    if (start == end) {
        arr[idx] = val;
        segtree[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update_segtree(2 * node, start, mid, idx, val);
        } else {
            update_segtree(2 * node + 1, mid + 1, end, idx, val);
        }
        segtree[node] = (segtree[2 * node] > segtree[2 * node + 1]) ? segtree[2 * node] : segtree[2 * node + 1];
    }
}

int main() {
    int M, D;
    scanf("%d %d", &M, &D);

    char op[2];
    ll n;
    int L;

    for (int i = 0; i < M; i++) {
        scanf("%s", op);
        if (op[0] == 'A') {
            scanf("%lld", &n);
            n = (n + last_query_result) % D;
            arr[arr_size] = n;
            arr_size++;
            update_segtree(1, 0, arr_size - 1, arr_size - 1, n);
        } else if (op[0] == 'Q') {
            scanf("%d", &L);
            last_query_result = query_segtree(1, 0, arr_size - 1, arr_size - L, arr_size - 1);
            printf("%lld\n", last_query_result);
        }
    }

    return 0;
}