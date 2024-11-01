#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200000
#define MAX_Q 200000

typedef long long ll;

int N, Q;
int S[MAX_N + 1];
int T[MAX_Q], L[MAX_Q], R[MAX_Q];

int seg[MAX_N * 4];
int lazy[MAX_N * 4];

void push_up(int node) {
    seg[node] = (seg[node * 2] > seg[node * 2 + 1]) ? seg[node * 2] : seg[node * 2 + 1];
}

void build(int node, int start, int end) {
    if (start == end) {
        seg[node] = S[start];
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    push_up(node);
}

void push_down(int node, int start, int end) {
    if (lazy[node] != 0) {
        seg[node] = lazy[node];
        if (start != end) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int l, int r, int val) {
    push_down(node, start, end);
    if (l > end || r < start) return;
    if (l <= start && end <= r) {
        seg[node] = val;
        if (start != end) {
            lazy[node * 2] = val;
            lazy[node * 2 + 1] = val;
        }
        return;
    }
    int mid = (start + end) / 2;
    update(node * 2, start, mid, l, r, val);
    update(node * 2 + 1, mid + 1, end, l, r, val);
    push_up(node);
}

int query(int node, int start, int end, int l, int r) {
    push_down(node, start, end);
    if (l > end || r < start) return 0;
    if (l <= start && end <= r) return seg[node];
    int mid = (start + end) / 2;
    int left = query(node * 2, start, mid, l, r);
    int right = query(node * 2 + 1, mid + 1, end, l, r);
    return (left > right) ? left : right;
}

int main() {
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &S[i]);
    }

    build(1, 1, N);

    for (int i = 0; i < Q; i++) {
        scanf("%d %d %d", &T[i], &L[i], &R[i]);
    }

    for (int i = 0; i < Q; i++) {
        ll cost = 0;
        for (int j = 1; j <= T[i]; j++) {
            update(1, 1, N, 1, N, query(1, 1, N, 1, N));
        }
        for (int j = L[i]; j <= R[i]; j++) {
            cost += query(1, 1, N, j, j);
        }
        printf("%lld\n", cost);

        // Reset the segment tree
        memset(lazy, 0, sizeof(lazy));
        build(1, 1, N);
    }

    return 0;
}