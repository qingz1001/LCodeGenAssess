#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAX_N 9
#define MAX_M 9

int n, m, c, op;
char grid[MAX_N][MAX_M + 1];
int dp[1 << (MAX_N * MAX_M)];

int main() {
    scanf("%d %d %d %d", &n, &m, &c, &op);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    int total_states = 1 << (n * m);
    dp[0] = 1;

    for (int state = 1; state < total_states; state++) {
        for (int pos = 0; pos < n * m; pos++) {
            if (!(state & (1 << pos))) continue;
            int x = pos / m, y = pos % m;
            if (grid[x][y] == '#') continue;

            int prev_state = state ^ (1 << pos);
            dp[state] = (dp[state] + (long long)dp[prev_state] * c) % MOD;
        }
    }

    int result = 0;
    if (op == 0) {
        result = dp[total_states - 1];
    } else {
        for (int state = 0; state < total_states; state++) {
            int rotated_state = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (state & (1 << (i * m + j))) {
                        rotated_state |= 1 << ((n - 1 - i) * m + (m - 1 - j));
                    }
                }
            }
            if (state <= rotated_state) {
                result = (result + dp[state]) % MOD;
            }
        }
    }

    printf("%d\n", result);
    return 0;
}