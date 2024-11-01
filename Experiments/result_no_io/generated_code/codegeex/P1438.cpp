#include <stdio.h>

int n, m, a[100005];

int main() {
    int i, opt, l, r, k, d, p;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (i = 0; i < m; i++) {
        scanf("%d", &opt);
        if (opt == 1) {
            scanf("%d%d%d%d", &l, &r, &k, &d);
            for (int j = l; j <= r; j++) {
                a[j] += k + (j - l) * d;
            }
        } else if (opt == 2) {
            scanf("%d", &p);
            printf("%d\n", a[p]);
        }
    }
    return 0;
}