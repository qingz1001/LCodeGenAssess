#include <stdio.h>
#include <string.h>

#define N 30005
#define MAX 30005

int n, m, a[N], b[N], c[N];
long long ans;

int lowbit(int x) {
    return x & -x;
}

void add(int x, int k) {
    while (x <= MAX) {
        c[x] += k;
        x += lowbit(x);
    }
}

int sum(int x) {
    int res = 0;
    while (x) {
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    for (int i = 1; i <= n; i++) {
        add(b[i], 1);
        ans += i - sum(b[i]);
    }
    for (int i = 1; i <= m; i++) {
        int op, l, r, x;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%d", &l, &r, &x);
            for (int j = l; j <= r; j++) {
                ans -= j - sum(b[j]);
                b[j] = x + j - l;
                ans += j - sum(b[j]);
            }
        } else {
            printf("%lld\n", ans);
        }
    }
    return 0;
}