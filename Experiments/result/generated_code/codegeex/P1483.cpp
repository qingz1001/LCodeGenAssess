#include <stdio.h>

#define MAXN 1000001

int n, m;
int a[MAXN];

int main() {
    int i, j, x, y;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (i = 0; i < m; i++) {
        scanf("%d", &j);
        if (j == 1) {
            scanf("%d%d", &x, &y);
            for (j = x; j <= n; j += x) {
                a[j] += y;
            }
        } else if (j == 2) {
            scanf("%d", &x);
            printf("%d\n", a[x]);
        }
    }
    return 0;
}