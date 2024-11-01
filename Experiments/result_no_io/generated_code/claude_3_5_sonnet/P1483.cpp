#include <stdio.h>
#include <string.h>

#define MAXN 1000001

long long a[MAXN];
long long d[MAXN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    memset(d, 0, sizeof(d));

    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int x;
            long long y;
            scanf("%d %lld", &x, &y);
            d[x] += y;
        } else if (op == 2) {
            int j;
            scanf("%d", &j);
            long long sum = a[j];
            for (int k = 1; k * k <= j; k++) {
                if (j % k == 0) {
                    sum += d[k];
                    if (k * k != j) {
                        sum += d[j / k];
                    }
                }
            }
            printf("%lld\n", sum);
        }
    }

    return 0;
}