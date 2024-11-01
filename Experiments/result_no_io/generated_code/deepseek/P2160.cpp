#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 70
#define INF INT_MAX

typedef struct {
    int h, t;
} Book;

int n;
Book books[MAXN];
int dp[MAXN][MAXN][MAXN];
int sum_t[MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int cmp(const void *a, const void *b) {
    return ((Book *)b)->h - ((Book *)a)->h;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &books[i].h, &books[i].t);
    }

    qsort(books, n, sizeof(Book), cmp);

    sum_t[0] = books[0].t;
    for (int i = 1; i < n; i++) {
        sum_t[i] = sum_t[i - 1] + books[i].t;
    }

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            for (int k = 0; k < MAXN; k++) {
                dp[i][j][k] = INF;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= sum_t[i]; j++) {
            for (int k = 0; k <= sum_t[i] - j; k++) {
                if (dp[i][j][k] == INF) continue;

                dp[i + 1][j + books[i].t][k] = min(dp[i + 1][j + books[i].t][k], dp[i][j][k] + (j + books[i].t == 0 ? 0 : books[i].h));
                dp[i + 1][j][k + books[i].t] = min(dp[i + 1][j][k + books[i].t], dp[i][j][k] + (k + books[i].t == 0 ? 0 : books[i].h));
                dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k] + (sum_t[i] - j - k == 0 ? 0 : books[i].h));
            }
        }
    }

    int ans = INF;
    for (int j = 1; j < sum_t[n - 1]; j++) {
        for (int k = 1; k < sum_t[n - 1] - j; k++) {
            if (dp[n][j][k] != INF) {
                ans = min(ans, dp[n][j][k] * max(max(j, k), sum_t[n - 1] - j - k));
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}