#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MOD 10007

int n, m;
int L[50001];
int dp[50001][1001];
int sum[50001];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int check(int x) {
    int cuts = 0;
    int current_sum = 0;
    for (int i = 1; i <= n; i++) {
        if (L[i] > x) return 0;
        if (current_sum + L[i] > x) {
            cuts++;
            current_sum = L[i];
        } else {
            current_sum += L[i];
        }
    }
    return cuts <= m;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &L[i]);
        sum[i] = sum[i - 1] + L[i];
    }

    int left = 1, right = sum[n];
    while (left < right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    int min_max_length = left;
    int ways = 0;

    for (int i = 0; i <= m; i++) {
        dp[0][i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j > 0) {
                int pos = i;
                while (pos > 0 && sum[i] - sum[pos - 1] <= min_max_length) {
                    dp[i][j] = (dp[i][j] + dp[pos - 1][j - 1]) % MOD;
                    pos--;
                }
            }
        }
    }

    ways = dp[n][m];

    printf("%d %d\n", min_max_length, ways);

    return 0;
}