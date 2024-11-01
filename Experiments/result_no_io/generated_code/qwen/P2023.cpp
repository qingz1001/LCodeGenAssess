#include <stdio.h>

#define MOD 1000000007

int main() {
    int n, p;
    scanf("%d %d", &n, &p);
    long long a[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    int m;
    scanf("%d", &m);

    while (m--) {
        int type, t, g, c;
        scanf("%d %d %d", &type, &t, &g);
        if (type == 1 || type == 2) {
            scanf("%d", &c);
        }

        if (type == 1) {
            for (int i = t; i <= g; i++) {
                a[i] = (a[i] * c) % p;
            }
        } else if (type == 2) {
            for (int i = t; i <= g; i++) {
                a[i] = (a[i] + c) % p;
            }
        } else if (type == 3) {
            long long sum = 0;
            for (int i = t; i <= g; i++) {
                sum = (sum + a[i]) % p;
            }
            printf("%lld\n", sum);
        }
    }

    return 0;
}