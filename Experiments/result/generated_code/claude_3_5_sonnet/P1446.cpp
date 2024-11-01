#include <stdio.h>
#include <string.h>

#define MAXN 60
#define MAXM 60

int sr, sb, sg, m, p;
int perm[MAXM][MAXN];
int fac[MAXN], inv[MAXN];
int dp[MAXN][MAXN][MAXN];

int pow_mod(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (long long)res * a % p;
        a = (long long)a * a % p;
        b >>= 1;
    }
    return res;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fac[i] = (long long)fac[i-1] * i % p;
    inv[MAXN-1] = pow_mod(fac[MAXN-1], p-2);
    for (int i = MAXN-2; i >= 0; i--)
        inv[i] = (long long)inv[i+1] * (i+1) % p;
}

int C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return (long long)fac[n] * inv[k] % p * inv[n-k] % p;
}

int main() {
    scanf("%d%d%d%d%d", &sr, &sb, &sg, &m, &p);
    int n = sr + sb + sg;
    
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &perm[i][j]);
    
    init();
    
    dp[0][0][0] = 1;
    for (int r = 0; r <= sr; r++) {
        for (int b = 0; b <= sb; b++) {
            for (int g = 0; g <= sg; g++) {
                if (r < sr) dp[r+1][b][g] = (dp[r+1][b][g] + dp[r][b][g]) % p;
                if (b < sb) dp[r][b+1][g] = (dp[r][b+1][g] + dp[r][b][g]) % p;
                if (g < sg) dp[r][b][g+1] = (dp[r][b][g+1] + dp[r][b][g]) % p;
            }
        }
    }
    
    int ans = dp[sr][sb][sg];
    for (int i = 1; i < m; i++) {
        int cycle[MAXN] = {0};
        int vis[MAXN] = {0};
        for (int j = 0; j < n; j++) {
            if (!vis[j]) {
                int len = 0, cur = j;
                do {
                    vis[cur] = 1;
                    cur = perm[i][cur] - 1;
                    len++;
                } while (cur != j);
                cycle[len]++;
            }
        }
        
        int tmp = 1;
        for (int j = 1; j <= n; j++) {
            tmp = (long long)tmp * pow_mod(j, cycle[j]) % p * inv[cycle[j]] % p;
        }
        ans = (ans + tmp) % p;
    }
    
    printf("%d\n", ans);
    return 0;
}