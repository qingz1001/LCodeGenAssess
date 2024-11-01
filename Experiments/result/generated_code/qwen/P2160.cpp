#include <stdio.h>
#include <stdlib.h>

#define MAXN 70
#define INF 1e9

int n;
int books[MAXN][2];
int dp[1 << MAXN][4];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int solve(int mask, int layer) {
    if (mask == 0) return INF;
    if (dp[mask][layer] != -1) return dp[mask][layer];

    int sum_h = 0, sum_t = 0, max_h = 0;
    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) != 0) {
            sum_h += books[i][0];
            sum_t += books[i][1];
            max_h = max(max_h, books[i][0]);
        }
    }

    int ans = INF;
    for (int j = 0; j < n; j++) {
        if ((mask & (1 << j)) != 0) {
            ans = min(ans, solve(mask ^ (1 << j), layer + 1));
        }
    }

    if (layer == 3) {
        ans = max_h * sum_t;
    } else {
        ans += solve(mask, layer);
    }

    dp[mask][layer] = ans;
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &books[i][0], &books[i][1]);
    }

    for (int i = 0; i < 1 << n; i++) {
        for (int j = 0; j <= 3; j++) {
            dp[i][j] = -1;
        }
    }

    printf("%d\n", solve((1 << n) - 1, 0));

    return 0;
}