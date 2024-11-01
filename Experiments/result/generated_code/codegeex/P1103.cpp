#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int height;
    int width;
} Book;

int compare(const void *a, const void *b) {
    Book *bookA = (Book *)a;
    Book *bookB = (Book *)b;
    return bookA->height - bookB->height;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    Book books[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
    }

    qsort(books, n, sizeof(Book), compare);

    int dp[n][n];
    memset(dp, 0x3f, sizeof(dp)); // Initialize dp array with a large number

    for (int i = 0; i < n; i++) {
        dp[i][i] = 0; // Base case: no cost to have a single book
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            for (int m = i; m < j; m++) {
                dp[i][j] = fmin(dp[i][j], dp[i][m] + dp[m + 1][j]);
            }
            if (len > k + 2) {
                dp[i][j] += books[j].width - books[i].width;
            }
        }
    }

    int minCost = dp[0][n - 1];
    for (int i = 1; i < n; i++) {
        minCost = fmin(minCost, dp[i][n - 1]);
    }

    printf("%d\n", minCost);
    return 0;
}