#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef long long ll;

ll a[MAXN];
ll p;

void update_multiply(int t, int g, ll c) {
    for (int i = t; i <= g; i++) {
        a[i] = (a[i] * c) % p;
    }
}

void update_add(int t, int g, ll c) {
    for (int i = t; i <= g; i++) {
        a[i] = (a[i] + c) % p;
    }
}

ll query_sum(int t, int g) {
    ll sum = 0;
    for (int i = t; i <= g; i++) {
        sum = (sum + a[i]) % p;
    }
    return sum;
}

int main() {
    int n, m;
    scanf("%d %lld", &n, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int op, t, g;
        ll c;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d %lld", &t, &g, &c);
            update_multiply(t, g, c);
        } else if (op == 2) {
            scanf("%d %d %lld", &t, &g, &c);
            update_add(t, g, c);
        } else if (op == 3) {
            scanf("%d %d", &t, &g);
            printf("%lld\n", query_sum(t, g));
        }
    }
    return 0;
}