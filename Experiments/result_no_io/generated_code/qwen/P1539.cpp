#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

int n, m;
char grid[225][225];
long long dp[225][225][2];

void read_input() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", grid[i]);
    }
}

void preprocess() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                dp[i][j][0] = dp[i][j][1] = 1;
            } else {
                dp[i][j][grid[i][j] - '0'] = 1;
            }
        }
    }
}

void solve() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] != '.') continue;
            long long sum = (dp[i][j][0] + dp[i][j][1]) % MOD;
            if (i > 0) {
                dp[i][j][0] = (dp[i][j][0] * sum) % MOD;
                dp[i][j][1] = (dp[i][j][1] * sum) % MOD;
            }
            if (j > 0) {
                dp[i][j][0] = (dp[i][j][0] * sum) % MOD;
                dp[i][j][1] = (dp[i][j][1] * sum) % MOD;
            }
        }
    }

    long long result = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] != '.') continue;
            result = (result + dp[i][j][0] + dp[i][j][1]) % MOD;
        }
    }

    printf("%lld\n", result);
}

int main() {
    read_input();
    preprocess();
    solve();
    return 0;
}