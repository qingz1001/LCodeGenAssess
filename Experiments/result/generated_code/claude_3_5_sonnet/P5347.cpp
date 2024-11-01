#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAX_N 9
#define MAX_M 9
#define MAX_STATE (1 << 16)

int n, m, c, op;
char grid[MAX_N][MAX_M + 1];
long long dp[MAX_N][MAX_M][MAX_STATE];
long long pow2[MAX_N * MAX_M + 1];

int encode_state(int state, int pos) {
    return (state & ~(3 << (pos * 2))) | (3 << (pos * 2));
}

int get_state(int state, int pos) {
    return (state >> (pos * 2)) & 3;
}

long long dfs(int x, int y, int state) {
    if (y == m) {
        y = 0;
        x++;
    }
    if (x == n) {
        return 1;
    }
    
    if (dp[x][y][state] != -1) {
        return dp[x][y][state];
    }
    
    long long res = 0;
    if (grid[x][y] == '#') {
        res = dfs(x, y + 1, state);
    } else {
        int up = y > 0 ? get_state(state, y - 1) : 0;
        int left = x > 0 ? get_state(state, m - 1) : 0;
        
        res = dfs(x, y + 1, state);
        
        if (!up && !left) {
            res = (res + dfs(x, y + 1, encode_state(state, y)) * (c - 1)) % MOD;
        }
        
        if (up == 1 && !left) {
            res = (res + dfs(x, y + 1, encode_state(state, y))) % MOD;
        }
        
        if (!up && left == 2) {
            res = (res + dfs(x, y + 1, encode_state(state, y))) % MOD;
        }
    }
    
    return dp[x][y][state] = res;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &c, &op);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    
    memset(dp, -1, sizeof(dp));
    
    pow2[0] = 1;
    for (int i = 1; i <= n * m; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }
    
    long long ans = dfs(0, 0, 0);
    
    if (op == 1) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '.') cnt++;
            }
        }
        ans = (ans + pow2[cnt]) * ((MOD + 1) / 2) % MOD;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}