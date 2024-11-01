#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 18
#define INF INT_MAX

int n;
int matrix[MAX_N][MAX_N];
int dp[1 << MAX_N];

int count_bits(int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

int solve() {
    int all = (1 << n) - 1;
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int state = 0; state <= all; state++) {
        if (dp[state] == INF) continue;

        for (int i = 0; i < n; i++) {
            if (state & (1 << i)) continue;

            int new_state = state | (1 << i);
            int cost = 0;

            for (int j = 0; j < n; j++) {
                int count = 0;
                if (i > 0 && (new_state & (1 << (i-1)))) count++;
                if (i < n-1 && (new_state & (1 << (i+1)))) count++;
                if (j > 0 && (new_state & (1 << (j-1)))) count++;
                if (j < n-1 && (new_state & (1 << (j+1)))) count++;

                if (count % 2 == 1 && matrix[i][j] == 0) {
                    cost++;
                }
            }

            if (dp[new_state] > dp[state] + cost) {
                dp[new_state] = dp[state] + cost;
            }
        }
    }

    return dp[all] == INF ? -1 : dp[all];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int result = solve();
    printf("%d\n", result);

    return 0;
}