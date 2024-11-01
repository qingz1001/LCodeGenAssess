#include <stdio.h>
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

int rotate_180(int state, int n, int m) {
    int new_state = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int bit = (state >> (i * m + j)) & 1;
            new_state |= bit << ((n - 1 - i) * m + (m - 1 - j));
        }
    }
    return new_state;
}

int solve(int x, int y, int state) {
    if (x == n) return 1;
    if (y == m) return solve(x + 1, 0, state);
    if (dp[x][y][state] != -1) return dp[x][y][state];

    int result = 0;
    if (grid[x][y] == '#') {
        result = solve(x, y + 1, state);
    } else {
        int up = (x > 0 && (state & (1 << ((x - 1) * m + y))) != 0);
        int down = (x < n - 1 && (state & (1 << ((x + 1) * m + y))) != 0);
        int left = (y > 0 && (state & (1 << (x * m + y - 1))) != 0);
        int right = (y < m - 1 && (state & (1 << (x * m + y + 1))) != 0);

        if (!up && !down && !left && !right) {
            result = (long long)c * solve(x, y + 1, state | (1 << (x * m + y))) % MOD;
        } else {
            result = solve(x, y + 1, state | (1 << (x * m + y)));
            if (up && !down) result = (result + solve(x, y + 1, state | (1 << ((x + 1) * m + y)))) % MOD;
            if (down && !up) result = (result + solve(x, y + 1, state | (1 << ((x - 1) * m + y)))) % MOD;
            if (left && !right) result = (result + solve(x, y + 1, state | (1 << (x * m + y + 1)))) % MOD;
            if (right && !left) result = (result + solve(x, y + 1, state | (1 << (x * m + y - 1)))) % MOD;
        }
    }

    dp[x][y][state] = result;
    return result;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &c, &op);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    memset(dp, -1, sizeof(dp));
    int result = solve(0, 0, 0);

    if (op == 1) {
        int rotated_result = solve(0, 0, rotate_180(0, n, m));
        result = (result + rotated_result) % MOD;
    }

    printf("%d\n", result);
    return 0;
}