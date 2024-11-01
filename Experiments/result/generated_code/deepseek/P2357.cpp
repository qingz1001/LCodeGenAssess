#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

typedef long long ll;

ll a[MAXN];
ll diff[MAXN];

void update(int l, int r, ll k) {
    diff[l] += k;
    if (r + 1 < MAXN) diff[r + 1] -= k;
}

ll query(int l, int r) {
    ll sum = 0;
    for (int i = 1; i <= r; i++) {
        a[i] += diff[i];
        if (i + 1 < MAXN) diff[i + 1] += diff[i];
        diff[i] = 0;
        if (i >= l) sum += a[i];
    }
    return sum;
}

int main() {
    int n, f;
    scanf("%d %d", &n, &f);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    while (f--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r;
            ll k;
            scanf("%d %d %lld", &l, &r, &k);
            update(l, r, k);
        } else if (op == 2) {
            ll k;
            scanf("%lld", &k);
            update(1, 1, k);
        } else if (op == 3) {
            ll k;
            scanf("%lld", &k);
            update(1, 1, -k);
        } else if (op == 4) {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(l, r));
        } else if (op == 5) {
            printf("%lld\n", a[1] + diff[1]);
        }
    }

    return 0;
}