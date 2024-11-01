#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define INF 1e9

typedef long long ll;

struct Node {
    ll cost;
    int inventory;
};

int n;
ll D[MAXN], U[MAXN], P[MAXN], M[MAXN], C[MAXN];
Node dp[MAXN];

void init() {
    for (int i = 0; i < n; ++i) {
        dp[i].cost = INF;
        dp[i].inventory = 0;
    }
}

ll min(ll a, ll b) {
    return a < b ? a : b;
}

void solve() {
    dp[0].cost = 0;
    dp[0].inventory = 0;

    for (int i = 1; i <= n; ++i) {
        int d = D[i - 1];
        int u = U[i - 1];
        int p = P[i - 1];
        int m = i == n ? 0 : M[i - 1];
        int c = i == n ? 0 : C[i - 1];

        // Produce new products
        for (int j = 0; j <= u && j <= d; ++j) {
            ll cost = dp[i - 1].cost + (d - j) * c + j * p;
            if (cost < dp[i].cost) {
                dp[i].cost = cost;
                dp[i].inventory = dp[i - 1].inventory + j - d;
            }
        }

        // Sell from inventory
        for (int j = 0; j <= dp[i - 1].inventory; ++j) {
            ll cost = dp[i - 1].cost + j * m;
            if (cost < dp[i].cost) {
                dp[i].cost = cost;
                dp[i].inventory = dp[i - 1].inventory - j;
            }
        }

        // Delay orders to next quarter
        for (int j = 0; j <= dp[i - 1].inventory; ++j) {
            ll cost = dp[i - 1].cost + j * c;
            if (cost < dp[i].cost) {
                dp[i].cost = cost;
                dp[i].inventory = dp[i - 1].inventory - j;
            }
        }
    }

    printf("%lld\n", dp[n].cost);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &D[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &U[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &P[i]);
    }
    for (int i = 0; i < n - 1; ++i) {
        scanf("%lld", &M[i]);
    }
    for (int i = 0; i < n - 1; ++i) {
        scanf("%lld", &C[i]);
    }

    init();
    solve();

    return 0;
}