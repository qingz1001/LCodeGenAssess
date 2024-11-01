#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MOD 1000000000

int n;
int tree[MAX_N][MAX_N];
int size[MAX_N];
long long f[MAX_N][2];
long long g[MAX_N][2];

void dfs(int u, int fa) {
    f[u][0] = g[u][0] = 1;
    f[u][1] = g[u][1] = 0;
    
    for (int i = 0; i < size[u]; i++) {
        int v = tree[u][i];
        if (v == fa) continue;
        
        dfs(v, u);
        
        f[u][1] += f[v][0];
        if (f[u][1] >= MOD) f[u][1] %= MOD;
        
        long long tmp = f[u][0] * f[v][0] % MOD;
        f[u][0] = (f[u][0] * (f[v][0] + f[v][1]) % MOD + f[u][1] * f[v][0] % MOD) % MOD;
        f[u][1] = (f[u][1] * (f[v][0] + f[v][1]) % MOD - tmp + MOD) % MOD;
        
        g[u][0] = g[u][0] * (g[v][0] + g[v][1]) % MOD;
        g[u][1] = (g[u][1] * (g[v][0] + g[v][1]) % MOD + g[u][0] * g[v][0] % MOD) % MOD;
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        int u, m;
        scanf("%d %d", &u, &m);
        size[u] = m;
        for (int j = 0; j < m; j++) {
            scanf("%d", &tree[u][j]);
        }
    }
    
    dfs(1, 0);
    
    printf("%lld\n", (f[1][0] + f[1][1]) % MOD);
    printf("%lld\n", (g[1][0] + g[1][1]) % MOD);
    
    return 0;
}