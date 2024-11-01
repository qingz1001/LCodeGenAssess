#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 15

typedef long long ll;

int n, m;
ll dp[1 << MAXN];

struct Edge {
    int a, b;
};

struct Group {
    int type;
    Edge edges[2];
};

Group groups[MAXN * MAXN];

ll mod_pow(ll base, ll exp) {
    ll result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int t;
        scanf("%d", &t);
        groups[i].type = t;
        if (t == 0) {
            scanf("%d %d", &groups[i].edges[0].a, &groups[i].edges[0].b);
            groups[i].edges[0].a--;
            groups[i].edges[0].b--;
        } else {
            scanf("%d %d %d %d", &groups[i].edges[0].a, &groups[i].edges[0].b, &groups[i].edges[1].a, &groups[i].edges[1].b);
            groups[i].edges[0].a--;
            groups[i].edges[0].b--;
            groups[i].edges[1].a--;
            groups[i].edges[1].b--;
        }
    }

    dp[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == 0) continue;
        for (int i = 0; i < m; i++) {
            int type = groups[i].type;
            if (type == 0) {
                int a = groups[i].edges[0].a;
                int b = groups[i].edges[0].b;
                if (!(mask & (1 << a)) && !(mask & (1 << (n + b)))) {
                    int new_mask = mask | (1 << a) | (1 << (n + b));
                    dp[new_mask] = (dp[new_mask] + dp[mask] * 500000004 % MOD) % MOD; // 500000004 = 2^-1 mod 10^9+7
                }
            } else if (type == 1) {
                int a1 = groups[i].edges[0].a;
                int b1 = groups[i].edges[0].b;
                int a2 = groups[i].edges[1].a;
                int b2 = groups[i].edges[1].b;
                if (!(mask & (1 << a1)) && !(mask & (1 << (n + b1))) && !(mask & (1 << a2)) && !(mask & (1 << (n + b2)))) {
                    int new_mask = mask | (1 << a1) | (1 << (n + b1)) | (1 << a2) | (1 << (n + b2));
                    dp[new_mask] = (dp[new_mask] + dp[mask] * 250000002 % MOD) % MOD; // 250000002 = 2^-2 mod 10^9+7
                }
            } else if (type == 2) {
                int a1 = groups[i].edges[0].a;
                int b1 = groups[i].edges[0].b;
                int a2 = groups[i].edges[1].a;
                int b2 = groups[i].edges[1].b;
                if (!(mask & (1 << a1)) && !(mask & (1 << (n + b1))) && !(mask & (1 << a2)) && !(mask & (1 << (n + b2)))) {
                    int new_mask1 = mask | (1 << a1) | (1 << (n + b1));
                    int new_mask2 = mask | (1 << a2) | (1 << (n + b2));
                    dp[new_mask1] = (dp[new_mask1] + dp[mask] * 500000004 % MOD) % MOD;
                    dp[new_mask2] = (dp[new_mask2] + dp[mask] * 500000004 % MOD) % MOD;
                }
            }
        }
    }

    ll E = dp[(1 << (2 * n)) - 1];
    ll result = (E * mod_pow(2, n)) % MOD;
    printf("%lld\n", result);

    return 0;
}