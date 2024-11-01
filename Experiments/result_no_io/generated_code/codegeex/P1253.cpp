#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

int n, q;
int a[MAXN];
int lazy_add[MAXN], lazy_set[MAXN];

void apply_add(int l, int r, int x) {
    for (int i = l; i <= r; i++) {
        a[i] += x;
    }
}

void apply_set(int l, int r, int x) {
    for (int i = l; i <= r; i++) {
        a[i] = x;
    }
}

void push_down(int l, int r) {
    if (lazy_set[l]) {
        apply_set(l, r, lazy_set[l]);
        lazy_set[l] = 0;
    }
    if (lazy_add[l]) {
        apply_add(l, r, lazy_add[l]);
        lazy_add[l] = 0;
    }
}

void update_add(int l, int r, int x) {
    push_down(l, r);
    apply_add(l, r, x);
    if (l < r) {
        lazy_add[l] += x;
        lazy_add[r + 1] -= x;
    }
}

void update_set(int l, int r, int x) {
    push_down(l, r);
    apply_set(l, r, x);
    if (l < r) {
        lazy_set[l] = x;
        lazy_set[r + 1] = 0;
    }
}

int query_max(int l, int r) {
    push_down(l, r);
    int max_val = a[l];
    for (int i = l + 1; i <= r; i++) {
        if (a[i] > max_val) {
            max_val = a[i];
        }
    }
    return max_val;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < q; i++) {
        int op, l, r, x;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 1) {
            scanf("%d", &x);
            update_set(l, r, x);
        } else if (op == 2) {
            scanf("%d", &x);
            update_add(l, r, x);
        } else if (op == 3) {
            printf("%d\n", query_max(l, r));
        }
    }
    return 0;
}