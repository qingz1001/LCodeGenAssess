#include <stdio.h>
#include <stdlib.h>

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
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
        for (int j = i + 1; j < n; j++) {
            dp[i][j] = dp[i][j - 1] + abs(books[j].width - books[j - 1].width);
        }
    }

    int minDisorder = dp[0][n - 1];
    for (int i = 0; i < n - k; i++) {
        for (int j = i + k; j < n; j++) {
            int disorder = dp[i + 1][j] + dp[i][j - k - 1] - dp[i + 1][j - k - 1];
            if (disorder < minDisorder) {
                minDisorder = disorder;
            }
        }
    }

    printf("%d\n", minDisorder);
    return 0;
}