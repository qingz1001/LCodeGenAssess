#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MOD 10000

typedef long long ll;

int n, t;
int nxt[MAXN][11];
ll f[MAXN];

void init() {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 1; j <= n; j++) {
            nxt[i][j] = -1;
        }
    }
}

void build(int *s, int m) {
    for (int i = m - 1; i >= 0; i--) {
        for (int j = 1; j <= n; j++) {
            nxt[i][j] = nxt[i + 1][j];
        }
        nxt[i][s[i]] = i;
    }
}

ll calc(int *s, int m) {
    for (int i = 0; i < MAXN; i++) {
        f[i] = 0;
    }
    f[m] = 1;
    for (int i = m; i < MAXN; i++) {
        for (int j = 1; j <= n; j++) {
            if (nxt[i][j] != -1) {
                f[nxt[i][j]] = (f[nxt[i][j]] + f[i]) % MOD;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        ans = (ans + f[i]) % MOD;
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &t);
    while (t--) {
        int m;
        scanf("%d", &m);
        int s[MAXN];
        for (int i = 0; i < m; i++) {
            scanf("%d", &s[i]);
        }
        init();
        build(s, m);
        ll ans = calc(s, m);
        if (ans < 1000) {
            printf("0");
        }
        if (ans < 100) {
            printf("0");
        }
        if (ans < 10) {
            printf("0");
        }
        printf("%lld\n", ans);
    }
    return 0;
}