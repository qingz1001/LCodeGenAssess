#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200000
#define MAX_Q 200000

typedef long long ll;

int N, Q;
int S[MAX_N + 1];
int T[MAX_Q], L[MAX_Q], R[MAX_Q];

struct Node {
    int l, r;
    ll max, sum;
} tree[MAX_N * 4];

void build(int node, int l, int r) {
    tree[node].l = l;
    tree[node].r = r;
    if (l == r) {
        tree[node].max = tree[node].sum = S[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node].max = (tree[node * 2].max > tree[node * 2 + 1].max) ? tree[node * 2].max : tree[node * 2 + 1].max;
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
}

ll query_sum(int node, int l, int r) {
    if (tree[node].l >= l && tree[node].r <= r) return tree[node].sum;
    if (tree[node].l > r || tree[node].r < l) return 0;
    return query_sum(node * 2, l, r) + query_sum(node * 2 + 1, l, r);
}

ll query_max(int node, int l, int r) {
    if (tree[node].l >= l && tree[node].r <= r) return tree[node].max;
    if (tree[node].l > r || tree[node].r < l) return 0;
    ll max_left = query_max(node * 2, l, r);
    ll max_right = query_max(node * 2 + 1, l, r);
    return (max_left > max_right) ? max_left : max_right;
}

void update(int node, int pos, int val) {
    if (tree[node].l == tree[node].r) {
        tree[node].max = tree[node].sum = val;
        return;
    }
    int mid = (tree[node].l + tree[node].r) / 2;
    if (pos <= mid) update(node * 2, pos, val);
    else update(node * 2 + 1, pos, val);
    tree[node].max = (tree[node * 2].max > tree[node * 2 + 1].max) ? tree[node * 2].max : tree[node * 2 + 1].max;
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
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
        int t = T[i], l = L[i], r = R[i];
        ll result = query_sum(1, l, r);
        printf("%lld\n", result);
        
        ll prev_max = 0;
        for (int j = l; j <= r; j++) {
            ll cur_max = (j > 1) ? query_max(1, j - 1, j - 1) : 0;
            cur_max = (cur_max > prev_max) ? cur_max : prev_max;
            update(1, j, cur_max);
            prev_max = cur_max;
        }
    }
    
    return 0;
}