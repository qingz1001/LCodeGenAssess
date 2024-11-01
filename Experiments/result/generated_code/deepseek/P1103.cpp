#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100

typedef struct {
    int height;
    int width;
} Book;

int compareBooks(const void *a, const void *b) {
    return ((Book *)a)->height - ((Book *)b)->height;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    Book books[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
    }

    qsort(books, n, sizeof(Book), compareBooks);

    int dp[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    dp[0][0] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            if (dp[i-1][j] != INT_MAX) {
                dp[i][j] = min(dp[i][j], dp[i-1][j] + abs(books[i].width - books[i-1].width));
            }
            if (j > 0) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
            }
        }
    }

    int result = INT_MAX;
    for (int j = 0; j <= k; j++) {
        result = min(result, dp[n-1][j]);
    }

    printf("%d\n", result);

    return 0;
}