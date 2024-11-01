#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 505
#define MAX_M 505
#define INF 0x3f3f3f3f

int n, m;
int height[MAX_N][MAX_M];
int dp[MAX_N][MAX_M];
bool can_reach[MAX_N][MAX_M];

int min(int a, int b) {
    return a < b ? a : b;
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    memset(can_reach, false, sizeof(can_reach));

    for (int j = 0; j < m; j++) {
        dp[0][j] = 1;
        can_reach[0][j] = true;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j > 0 && height[i][j] < height[i-1][j-1] && can_reach[i-1][j-1]) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
                can_reach[i][j] = true;
            }
            if (height[i][j] < height[i-1][j] && can_reach[i-1][j]) {
                dp[i][j] = min(dp[i][j], dp[i-1][j]);
                can_reach[i][j] = true;
            }
            if (j < m-1 && height[i][j] < height[i-1][j+1] && can_reach[i-1][j+1]) {
                dp[i][j] = min(dp[i][j], dp[i-1][j+1]);
                can_reach[i][j] = true;
            }
        }
    }

    int min_factories = INF;
    int unreachable = 0;
    for (int j = 0; j < m; j++) {
        if (can_reach[n-1][j]) {
            min_factories = min(min_factories, dp[n-1][j]);
        } else {
            unreachable++;
        }
    }

    if (unreachable == 0) {
        printf("1\n%d\n", min_factories);
    } else {
        printf("0\n%d\n", unreachable);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &height[i][j]);
        }
    }
    solve();
    return 0;
}