#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100

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

    Book books[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
    }

    // Sort books by height
    qsort(books, n, sizeof(Book), compareBooks);

    // dp[i][j] represents the minimum messiness when considering the first i+1 books and removing j books
    int dp[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    // Initialize the first book
    dp[0][0] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            if (dp[i-1][j] != INT_MAX) {
                // Option 1: Keep the i-th book
                dp[i][j] = min(dp[i][j], dp[i-1][j] + abs(books[i].width - books[i-1].width));

                // Option 2: Remove the i-th book
                if (j < k) {
                    dp[i][j+1] = min(dp[i][j+1], dp[i-1][j]);
                }
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