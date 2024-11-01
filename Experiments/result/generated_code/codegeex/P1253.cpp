#include <stdio.h>
#include <limits.h>

#define MAXN 1000001

int n, q;
int a[MAXN];

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    while (q--) {
        int op, l, r, x;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d %d", &l, &r, &x);
            for (int i = l; i <= r; i++) {
                a[i] = x;
            }
        } else if (op == 2) {
            scanf("%d %d %d", &l, &r, &x);
            for (int i = l; i <= r; i++) {
                a[i] += x;
            }
        } else if (op == 3) {
            scanf("%d %d", &l, &r);
            int max_val = INT_MIN;
            for (int i = l; i <= r; i++) {
                if (a[i] > max_val) {
                    max_val = a[i];
                }
            }
            printf("%d\n", max_val);
        }
    }

    return 0;
}