#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 70

typedef struct {
    int h, t;
} Book;

Book books[MAXN];
int n;
int dp[MAXN][MAXN][MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int cmp(const void *a, const void *b) {
    return ((Book *)b)->t - ((Book *)a)->t;
}

int solve() {
    qsort(books, n, sizeof(Book), cmp);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                dp[i][j][k] = INT_MAX;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k <= i - j; k++) {
                if (dp[i][j][k] == INT_MAX) continue;

                int l = i - j - k;

                if (j == 0) {
                    dp[i + 1][j + 1][k] = min(dp[i + 1][j + 1][k], dp[i][j][k] + books[i].h);
                } else {
                    dp[i + 1][j + 1][k] = min(dp[i + 1][j + 1][k], dp[i][j][k]);
                }

                if (k == 0) {
                    dp[i + 1][j][k + 1] = min(dp[i + 1][j][k + 1], dp[i][j][k] + books[i].h);
                } else {
                    dp[i + 1][j][k + 1] = min(dp[i + 1][j][k + 1], dp[i][j][k]);
                }

                if (l == 0) {
                    dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k] + books[i].h);
                } else {
                    dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k]);
                }
            }
        }
    }

    int ans = INT_MAX;
    for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n - j; k++) {
            int l = n - j - k;
            if (l > 0) {
                int max_height = max(dp[n][j][k], max(dp[n][j][k], dp[n][j][k]));
                int max_width = max(j, max(k, l)) * books[0].t;
                ans = min(ans, max_height * max_width);
            }
        }
    }

    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &books[i].h, &books[i].t);
    }

    int result = solve();
    printf("%d\n", result);

    return 0;
}