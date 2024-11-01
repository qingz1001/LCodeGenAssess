#include <stdio.h>
#include <stdlib.h>

#define MAXN 61
#define MOD 100

int S_r, S_b, S_g, m, P;
int n;
int shuffle[MAXN][MAXN];
int visited[MAXN];
int color[MAXN];
int dp[21][21][21];

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int mod_inverse(int a, int p) {
    int m0 = p, t, q;
    int x0 = 0, x1 = 1;
    if (p == 1) return 0;
    while (a > 1) {
        q = a / p;
        t = p;
        p = a % p;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

int factorial[MAXN];
int inv_factorial[MAXN];

void precompute_factorials() {
    factorial[0] = 1;
    inv_factorial[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % P;
        inv_factorial[i] = mod_inverse(factorial[i], P);
    }
}

int comb(int n, int k) {
    if (k > n) return 0;
    return (factorial[n] * inv_factorial[k] % P) * inv_factorial[n - k] % P;
}

void dfs(int u, int* cycle_size) {
    visited[u] = 1;
    (*cycle_size)++;
    for (int v = 1; v <= n; v++) {
        if (shuffle[u][v] && !visited[v]) {
            dfs(v, cycle_size);
        }
    }
}

int solve() {
    int total_ways = 0;
    for (int r = 0; r <= S_r; r++) {
        for (int b = 0; b <= S_b; b++) {
            for (int g = 0; g <= S_g; g++) {
                if (r + b + g == n) {
                    dp[r][b][g] = comb(S_r, r) * comb(S_b, b) % P * comb(S_g, g) % P;
                    total_ways = (total_ways + dp[r][b][g]) % P;
                }
            }
        }
    }
    return total_ways;
}

int main() {
    scanf("%d %d %d %d %d", &S_r, &S_b, &S_g, &m, &P);
    n = S_r + S_b + S_g;
    precompute_factorials();

    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &shuffle[i][j]);
        }
    }

    int result = solve();
    printf("%d\n", result);

    return 0;
}