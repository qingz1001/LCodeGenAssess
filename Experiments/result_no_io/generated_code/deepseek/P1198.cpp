#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 200005

typedef long long ll;

ll arr[MAX_M];
ll segTree[4 * MAX_M];
ll last_query_result = 0;
ll D;

void buildSegmentTree(int node, int start, int end) {
    if (start == end) {
        segTree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        buildSegmentTree(2 * node, start, mid);
        buildSegmentTree(2 * node + 1, mid + 1, end);
        segTree[node] = (segTree[2 * node] > segTree[2 * node + 1]) ? segTree[2 * node] : segTree[2 * node + 1];
    }
}

ll querySegmentTree(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return -1;
    }
    if (l <= start && end <= r) {
        return segTree[node];
    }
    int mid = (start + end) / 2;
    ll left = querySegmentTree(2 * node, start, mid, l, r);
    ll right = querySegmentTree(2 * node + 1, mid + 1, end, l, r);
    return (left > right) ? left : right;
}

void updateSegmentTree(int node, int start, int end, int idx, ll val) {
    if (start == end) {
        arr[idx] = val;
        segTree[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            updateSegmentTree(2 * node, start, mid, idx, val);
        } else {
            updateSegmentTree(2 * node + 1, mid + 1, end, idx, val);
        }
        segTree[node] = (segTree[2 * node] > segTree[2 * node + 1]) ? segTree[2 * node] : segTree[2 * node + 1];
    }
}

int main() {
    int M;
    scanf("%d %lld", &M, &D);

    int arr_size = 0;
    char op[2];
    ll n;
    int L;

    for (int i = 0; i < M; i++) {
        scanf("%s", op);
        if (op[0] == 'Q') {
            scanf("%d", &L);
            last_query_result = querySegmentTree(1, 0, arr_size - 1, arr_size - L, arr_size - 1);
            printf("%lld\n", last_query_result);
        } else if (op[0] == 'A') {
            scanf("%lld", &n);
            n = (n + last_query_result) % D;
            updateSegmentTree(1, 0, arr_size, arr_size, n);
            arr_size++;
        }
    }

    return 0;
}