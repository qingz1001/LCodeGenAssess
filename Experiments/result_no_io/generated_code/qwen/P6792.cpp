#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXQ 200005

int a[MAXN];
int maxa[MAXN];

void update(int l, int r, int x) {
    for (int i = l; i <= r; i++) {
        if (a[i] < x) {
            a[i] = x;
            maxa[i] = x;
        }
    }
}

int query(int l, int r) {
    int max_sum = 0;
    int current_sum = 0;
    for (int i = l; i <= r; i++) {
        current_sum += maxa[i];
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
        if (current_sum < 0) {
            current_sum = 0;
        }
    }
    return max_sum;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        maxa[i] = a[i];
    }

    while (q--) {
        int op, l, r, x;
        scanf("%d", &op);
        if (op == 0) {
            scanf("%d %d %d %d", &l, &r, &x);
            update(l, r, x);
        } else {
            scanf("%d %d", &l, &r);
            printf("%d\n", query(l, r));
        }
    }

    return 0;
}