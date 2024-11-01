#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_M 500
#define MAX_K 500

int m, k;
int books[MAX_M];
long long dp[MAX_M][MAX_K];
int split[MAX_M][MAX_K];

long long max(long long a, long long b) {
    return a > b ? a : b;
}

void solve() {
    for (int i = 0; i < m; i++) {
        dp[i][0] = LLONG_MAX;
    }

    for (int j = 0; j < k; j++) {
        dp[0][j] = books[0];
        split[0][j] = 0;
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < k; j++) {
            dp[i][j] = LLONG_MAX;
            long long sum = 0;
            for (int p = i; p >= j; p--) {
                sum += books[p];
                long long maxPages = max(dp[p-1][j-1], sum);
                if (maxPages < dp[i][j]) {
                    dp[i][j] = maxPages;
                    split[i][j] = p;
                }
            }
        }
    }
}

void print_result() {
    int start = m - 1;
    for (int j = k - 1; j >= 0; j--) {
        int end = start;
        start = split[start][j];
        printf("%d %d\n", start + 1, end + 1);
    }
}

int main() {
    scanf("%d %d", &m, &k);
    for (int i = 0; i < m; i++) {
        scanf("%d", &books[i]);
    }

    solve();
    print_result();

    return 0;
}