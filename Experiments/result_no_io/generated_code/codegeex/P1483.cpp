#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n+1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    while (m--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            for (int k = 1; k * x <= n; k++) {
                a[k * x] += y;
            }
        } else if (op == 2) {
            int j;
            scanf("%d", &j);
            printf("%d\n", a[j]);
        }
    }
    return 0;
}