#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50
#define MAXM 9
#define MOD 10

int n, m;
int nums[MAXN];
int dp_min[MAXN][MAXN][MAXM];
int dp_max[MAXN][MAXN][MAXM];

int mod(int x) {
    return ((x % MOD) + MOD) % MOD;
}

void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k <= m; k++) {
                dp_min[i][j][k] = INT_MAX;
                dp_max[i][j][k] = INT_MIN;
            }
        }
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        dp_min[i][i][1] = dp_max[i][i][1] = mod(nums[i]);
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i < n; i++) {
            int j = (i + len - 1) % n;
            for (int k = 2; k <= m; k++) {
                for (int p = 1; p < len; p++) {
                    int q = (i + p) % n;
                    for (int l = 1; l < k; l++) {
                        if (dp_min[i][q][l] != INT_MAX && dp_min[q + 1][j][k - l] != INT_MAX) {
                            dp_min[i][j][k] = fmin(dp_min[i][j][k], mod(dp_min[i][q][l] * dp_min[q + 1][j][k - l]));
                        }
                        if (dp_max[i][q][l] != INT_MIN && dp_max[q + 1][j][k - l] != INT_MIN) {
                            dp_max[i][j][k] = fmax(dp_max[i][j][k], mod(dp_max[i][q][l] * dp_max[q + 1][j][k - l]));
                        }
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    init();
    solve();

    int min_result = INT_MAX;
    int max_result = INT_MIN;
    for (int i = 0; i < n; i++) {
        min_result = fmin(min_result, dp_min[i][(i + n - 1) % n][m]);
        max_result = fmax(max_result, dp_max[i][(i + n - 1) % n][m]);
    }

    printf("%d\n%d\n", min_result, max_result);

    return 0;
}