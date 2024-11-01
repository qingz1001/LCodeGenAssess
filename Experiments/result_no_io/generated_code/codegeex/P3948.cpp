#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000010

int n, opt, mod, min, max, final;
int a[MAXN];

void add(int l, int r, int x) {
    for (int i = l; i <= r; i++) {
        a[i] += x;
    }
}

int query(int l, int r) {
    int count = 0;
    for (int i = l; i <= r; i++) {
        if (min <= a[i] * i % mod && a[i] * i % mod <= max) {
            count++;
        }
    }
    return count;
}

int main() {
    scanf("%d %d %d %d %d", &n, &opt, &mod, &min, &max);
    for (int i = 1; i <= n; i++) {
        a[i] = 0;
    }
    for (int i = 0; i < opt; i++) {
        char op;
        int l, r, x;
        scanf(" %c %d %d", &op, &l, &r);
        if (op == 'A') {
            scanf("%d", &x);
            add(l, r, x);
        } else if (op == 'Q') {
            printf("%d\n", query(l, r));
        }
    }
    scanf("%d", &final);
    for (int i = 0; i < final; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", query(l, r));
    }
    return 0;
}