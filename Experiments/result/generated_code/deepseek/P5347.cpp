#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MOD 998244353

int n, m, c, op;
char grid[10][10];
int dp[10][10][1 << 18];

int count_bits(int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

int solve(int x, int y, int mask) {
    if (x == n) return 1;
    if (y == m) return solve(x + 1, 0, mask);
    if (dp[x][y][mask] != -1) return dp[x][y][mask];

    int result = 0;
    if (grid[x][y] == '#') {
        result = solve(x, y + 1, mask);
    } else {
        int current_cell = x * m + y;
        int current_bit = 1 << current_cell;
        int up_bit = 1 << (current_cell - m);
        int left_bit = 1 << (current_cell - 1);

        if (!(mask & current_bit)) {
            // Case 1: Draw a new line
            result = (result + (long long)c * solve(x, y + 1, mask | current_bit)) % MOD;

            // Case 2: Draw a vertical line if possible
            if (x > 0 && (mask & up_bit)) {
                result = (result + solve(x, y + 1, mask | current_bit)) % MOD;
            }

            // Case 3: Draw a horizontal line if possible
            if (y > 0 && (mask & left_bit)) {
                result = (result + solve(x, y + 1, mask | current_bit)) % MOD;
            }
        } else {
            // Case 4: Continue the line
            result = solve(x, y + 1, mask);
        }
    }

    dp[x][y][mask] = result;
    return result;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &c, &op);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    memset(dp, -1, sizeof(dp));
    int result = solve(0, 0, 0);

    printf("%d\n", result);
    return 0;
}