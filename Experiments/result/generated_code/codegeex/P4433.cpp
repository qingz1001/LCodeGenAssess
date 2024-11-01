#include <stdio.h>
#include <stdlib.h>

#define MAXN 50000

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    int l[MAXN], r[MAXN], a[MAXN], b[MAXN];
    int type[MAXN], mod_sum[MAXN], mod_sum2[MAXN];
    long long sum[MAXN];

    for (int i = 0; i < q; i++) {
        scanf("%d", &type[i]);
        if (type[i] == 1) {
            scanf("%d %d %d %d", &l[i], &r[i], &a[i], &b[i]);
        } else {
            scanf("%d %d", &l[i], &r[i]);
        }
    }

    for (int i = 0; i < q; i++) {
        if (type[i] == 1) {
            int L = l[i], R = r[i], A = a[i], B = b[i];
            for (int j = L; j <= R; j++) {
                sum[j] = (long long)(j - L + 1) * A % B;
            }
        } else {
            int L = l[i], R = r[i];
            long long res = 0;
            for (int j = L; j <= R; j++) {
                res += sum[j];
            }
            printf("%lld\n", res);
        }
    }

    return 0;
}