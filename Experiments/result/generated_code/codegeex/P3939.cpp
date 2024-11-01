#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int a[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    while (m--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int l, r, c;
            scanf("%d %d %d", &l, &r, &c);
            int count = 0;
            for (int i = l; i <= r; i++) {
                if (a[i] == c) {
                    count++;
                }
            }
            printf("%d\n", count);
        } else if (op == 2) {
            int x;
            scanf("%d", &x);
            int temp = a[x];
            a[x] = a[x + 1];
            a[x + 1] = temp;
        }
    }

    return 0;
}