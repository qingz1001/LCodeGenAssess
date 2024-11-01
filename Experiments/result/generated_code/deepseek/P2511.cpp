#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MOD 10007

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int check(int* L, int n, int m, int max_len) {
    int cuts = 0;
    int current_len = 0;
    for (int i = 0; i < n; i++) {
        if (current_len + L[i] > max_len) {
            cuts++;
            current_len = L[i];
        } else {
            current_len += L[i];
        }
    }
    return cuts <= m;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int* L = (int*)malloc(n * sizeof(int));
    int total_len = 0;
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &L[i]);
        total_len += L[i];
        max_len = max(max_len, L[i]);
    }

    int left = max_len;
    int right = total_len;
    int min_max_len = right;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(L, n, m, mid)) {
            min_max_len = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    int dp[1001][1001] = {0};
    int sum[1001][1001] = {0};
    dp[0][0] = 1;
    sum[0][0] = 1;

    int current_len = 0;
    for (int i = 1; i <= n; i++) {
        current_len += L[i - 1];
        for (int j = 1; j <= m + 1; j++) {
            if (j > i) break;
            dp[i][j] = sum[i - 1][j - 1];
            if (current_len <= min_max_len) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }
            sum[i][j] = (sum[i - 1][j] + dp[i][j]) % MOD;
        }
    }

    int ways = 0;
    for (int j = 1; j <= m + 1; j++) {
        ways = (ways + dp[n][j]) % MOD;
    }

    printf("%d %d\n", min_max_len, ways);

    free(L);
    return 0;
}