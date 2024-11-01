#include <stdio.h>
#include <string.h>

#define MAXN 60
#define MOD 100

int sr, sb, sg, m, p;
int perm[MAXN][MAXN];
int tmp[MAXN];
int fac[MAXN];
int inv[MAXN];

int powmod(int base, int exp) {
    int res = 1;
    while (exp) {
        if (exp & 1) res = (long long)res * base % p;
        base = (long long)base * base % p;
        exp >>= 1;
    }
    return res;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = (long long)fac[i-1] * i % p;
    }
    inv[MAXN-1] = powmod(fac[MAXN-1], p-2);
    for (int i = MAXN-2; i >= 0; i--) {
        inv[i] = (long long)inv[i+1] * (i+1) % p;
    }
}

int C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return (long long)fac[n] * inv[k] % p * inv[n-k] % p;
}

void mul(int a[MAXN], int b[MAXN]) {
    for (int i = 0; i < m; i++) {
        tmp[i] = a[b[i]];
    }
    memcpy(a, tmp, sizeof(tmp));
}

int main() {
    scanf("%d%d%d%d%d", &sr, &sb, &sg, &m, &p);
    init();
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &perm[i][j]);
            perm[i][j]--;
        }
    }
    
    int cycle[MAXN] = {0};
    int vis[MAXN] = {0};
    for (int i = 0; i < m; i++) {
        if (!vis[i]) {
            int len = 0, cur = i;
            while (!vis[cur]) {
                vis[cur] = 1;
                cur = perm[0][cur];
                len++;
            }
            cycle[len]++;
        }
    }
    
    int ans = 1;
    for (int i = 1; i <= m; i++) {
        if (cycle[i]) {
            int sum = 0;
            for (int j = 0; j <= sr / i; j++) {
                for (int k = 0; k <= sb / i; k++) {
                    int g = (sg - i * j - i * k) / i;
                    if (g >= 0 && i * (j + k + g) == sr + sb + sg) {
                        sum = (sum + (long long)C(cycle[i], j) * C(cycle[i] - j, k) % p) % p;
                    }
                }
            }
            ans = (long long)ans * sum % p;
        }
    }
    
    printf("%d\n", ans);
    return 0;
}