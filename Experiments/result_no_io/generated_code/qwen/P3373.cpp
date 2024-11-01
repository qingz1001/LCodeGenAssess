#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MOD 571373

typedef struct {
    int add;
    int mul;
} Node;

Node tree[MAXN * 4];
int arr[MAXN];

void push_up(int node) {
    tree[node].add = (tree[node].add + tree[node << 1].add + tree[node << 1 | 1].add) % MOD;
    tree[node].mul = (tree[node].mul * tree[node << 1].mul % MOD * tree[node << 1 | 1].mul % MOD) % MOD;
}

void push_down(int node, int len) {
    if (tree[node].add != 0 || tree[node].mul != 1) {
        int left = node << 1, right = node << 1 | 1;
        tree[left].add = (tree[left].add * tree[node].mul + tree[node].add) % MOD;
        tree[right].add = (tree[right].add * tree[node].mul + tree[node].add) % MOD;
        tree[left].mul = tree[left].mul * tree[node].mul % MOD;
        tree[right].mul = tree[right].mul * tree[node].mul % MOD;
        tree[node].add = 0;
        tree[node].mul = 1;
    }
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node].add = 0;
        tree[node].mul = 1;
        tree[node].sum = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(node << 1, start, mid);
        build(node << 1 | 1, mid + 1, end);
        push_up(node);
    }
}

void update_add(int node, int start, int end, int l, int r, int val) {
    if (l <= start && end <= r) {
        tree[node].add = (tree[node].add + val) % MOD;
    } else {
        push_down(node, end - start + 1);
        int mid = (start + end) / 2;
        if (l <= mid) update_add(node << 1, start, mid, l, r, val);
        if (r > mid) update_add(node << 1 | 1, mid + 1, end, l, r, val);
        push_up(node);
    }
}

void update_mul(int node, int start, int end, int l, int r, int val) {
    if (l <= start && end <= r) {
        tree[node].mul = tree[node].mul * val % MOD;
        tree[node].add = tree[node].add * val % MOD;
    } else {
        push_down(node, end - start + 1);
        int mid = (start + end) / 2;
        if (l <= mid) update_mul(node << 1, start, mid, l, r, val);
        if (r > mid) update_mul(node << 1 | 1, mid + 1, end, l, r, val);
        push_up(node);
    }
}

long long query_sum(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node].sum;
    } else {
        push_down(node, end - start + 1);
        long long sum = 0;
        int mid = (start + end) / 2;
        if (l <= mid) sum += query_sum(node << 1, start, mid, l, r);
        if (r > mid) sum += query_sum(node << 1 | 1, mid + 1, end, l, r);
        return sum % MOD;
    }
}

int main() {
    int n, q, m;
    scanf("%d %d %d", &n, &q, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    build(1, 1, n);
    while (q--) {
        int type, x, y, k;
        scanf("%d", &type);
        switch (type) {
            case 1:
                scanf("%d %d %d", &x, &y, &k);
                update_mul(1, 1, n, x, y, k);
                break;
            case 2:
                scanf("%d %d %d", &x, &y, &k);
                update_add(1, 1, n, x, y, k);
                break;
            case 3:
                scanf("%d %d", &x, &y);
                printf("%lld\n", query_sum(1, 1, n, x, y));
                break;
        }
    }
    return 0;
}