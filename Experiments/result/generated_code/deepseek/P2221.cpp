#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MOD 1000000007

typedef long long ll;

ll n, m;
ll v[MAXN];
ll sum1[MAXN], sum2[MAXN], sum3[MAXN];

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

void update(ll l, ll r, ll val) {
    for (ll i = l; i <= r; i++) {
        v[i] += val;
    }
}

void query(ll l, ll r) {
    ll total_cost = 0;
    ll total_pairs = (r - l + 1) * (r - l) / 2;
    for (ll i = l; i < r; i++) {
        for (ll j = i + 1; j <= r; j++) {
            total_cost += (j - i) * v[i];
        }
    }
    ll g = gcd(total_cost, total_pairs);
    if (total_pairs == 1) {
        printf("%lld/1\n", total_cost);
    } else {
        printf("%lld/%lld\n", total_cost / g, total_pairs / g);
    }
}

int main() {
    scanf("%lld %lld", &n, &m);
    char op;
    ll l, r, val;
    for (ll i = 0; i < m; i++) {
        scanf(" %c", &op);
        if (op == 'C') {
            scanf("%lld %lld %lld", &l, &r, &val);
            update(l, r, val);
        } else if (op == 'Q') {
            scanf("%lld %lld", &l, &r);
            query(l, r);
        }
    }
    return 0;
}