#include <stdio.h>

int n, m;
int a[50005];

int main() {
    int i, j, k, l, r, x, c;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (i = 1; i <= m; i++) {
        scanf("%d", &k);
        if (k == 1) {
            scanf("%d%d%d", &l, &r, &c);
            int ans = 0;
            for (j = l; j <= r; j++)
                if (a[j] == c)
                    ans++;
            printf("%d\n", ans);
        } else {
            scanf("%d", &x);
            // 交换x和x+1位置的兔子
            int temp = a[x];
            a[x] = a[x + 1];
            a[x + 1] = temp;
        }
    }
    return 0;
}