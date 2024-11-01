#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 500005
#define MAX_M 20005

typedef long long ll;

int n, m;
ll tree[MAX_N * 4], lazy[MAX_N * 4];
int arr[MAX_N];

void push_down(int node, int l, int r) {
    if (lazy[node] != 0) {
        int mid = (l + r) / 2;
        tree[node * 2] += lazy[node] * (mid - l + 1);
        tree[node * 2 + 1] += lazy[node] * (r - mid);
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void update(int node, int l, int r, int ul, int ur, ll val) {
    if (ul <= l && r <= ur) {
        tree[node] += val * (r - l + 1);
        lazy[node] += val;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    if (ul <= mid) update(node * 2, l, mid, ul, ur, val);
    if (ur > mid) update(node * 2 + 1, mid + 1, r, ul, ur, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node];
    push_down(node, l, r);
    int mid = (l + r) / 2;
    ll sum = 0;
    if (ql <= mid) sum += query(node * 2, l, mid, ql, qr);
    if (qr > mid) sum += query(node * 2 + 1, mid + 1, r, ql, qr);
    return sum;
}

void insert(int posi, int tot) {
    for (int i = n; i > posi; i--) {
        arr[i + tot] = arr[i];
    }
    for (int i = 1; i <= tot; i++) {
        scanf("%d", &arr[posi + i]);
    }
    n += tot;
    build(1, 1, n);
}

void delete(int posi, int tot) {
    for (int i = posi + tot; i <= n; i++) {
        arr[i - tot] = arr[i];
    }
    n -= tot;
    build(1, 1, n);
}

void make_same(int posi, int tot, int c) {
    update(1, 1, n, posi, posi + tot - 1, c - query(1, 1, n, posi, posi) / tot);
}

void reverse(int posi, int tot) {
    int l = posi, r = posi + tot - 1;
    while (l < r) {
        int temp = arr[l];
        arr[l] = arr[r];
        arr[r] = temp;
        l++;
        r--;
    }
    build(1, 1, n);
}

ll get_sum(int posi, int tot) {
    return query(1, 1, n, posi, posi + tot - 1);
}

ll max_sum() {
    ll max_so_far = LLONG_MIN, max_ending_here = 0;
    for (int i = 1; i <= n; i++) {
        ll val = query(1, 1, n, i, i);
        max_ending_here += val;
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
        }
        if (max_ending_here < 0) {
            max_ending_here = 0;
        }
    }
    return max_so_far;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }
    build(1, 1, n);

    char op[20];
    int posi, tot, c;
    for (int i = 0; i < m; i++) {
        scanf("%s", op);
        if (strcmp(op, "INSERT") == 0) {
            scanf("%d %d", &posi, &tot);
            insert(posi, tot);
        } else if (strcmp(op, "DELETE") == 0) {
            scanf("%d %d", &posi, &tot);
            delete(posi, tot);
        } else if (strcmp(op, "MAKE-SAME") == 0) {
            scanf("%d %d %d", &posi, &tot, &c);
            make_same(posi, tot, c);
        } else if (strcmp(op, "REVERSE") == 0) {
            scanf("%d %d", &posi, &tot);
            reverse(posi, tot);
        } else if (strcmp(op, "GET-SUM") == 0) {
            scanf("%d %d", &posi, &tot);
            printf("%lld\n", get_sum(posi, tot));
        } else if (strcmp(op, "MAX-SUM") == 0) {
            printf("%lld\n", max_sum());
        }
    }

    return 0;
}