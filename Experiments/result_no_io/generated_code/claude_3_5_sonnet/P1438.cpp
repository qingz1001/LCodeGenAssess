#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

long long a[MAXN];
long long add[MAXN], d[MAXN];

void update(int l, int r, long long k, long long delta) {
    add[l] += k;
    add[r+1] -= k + (r-l)*delta;
    d[l] += delta;
    d[r+1] -= delta;
}

long long query(int p) {
    long long sum = a[p];
    long long delta_sum = 0;
    for (int i = 1; i <= p; i++) {
        delta_sum += d[i];
        sum += add[i] + delta_sum * (p - i);
    }
    return sum;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    memset(add, 0, sizeof(add));
    memset(d, 0, sizeof(d));

    for (int i = 0; i < m; i++) {
        int opt;
        scanf("%d", &opt);

        if (opt == 1) {
            int l, r;
            long long k, delta;
            scanf("%d %d %lld %lld", &l, &r, &k, &delta);
            update(l, r, k, delta);
        } else if (opt == 2) {
            int p;
            scanf("%d", &p);
            printf("%lld\n", query(p));
        }
    }

    return 0;
}