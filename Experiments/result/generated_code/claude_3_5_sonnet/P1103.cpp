#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100
#define INF 1000000000

typedef struct {
    int height;
    int width;
} Book;

int compare(const void *a, const void *b) {
    return ((Book *)a)->height - ((Book *)b)->height;
}

int main() {
    int n, k;
    Book books[MAX_N];
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
    }

    qsort(books, n, sizeof(Book), compare);

    int dp[MAX_N][MAX_N] = {0};

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dp[i][j] = dp[i][j-1] + abs(books[j].width - books[j-1].width);
        }
    }

    int result[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        result[i][0] = dp[0][i];
    }

    for (int j = 1; j <= k; j++) {
        for (int i = j; i < n; i++) {
            result[i][j] = INF;
            for (int m = j - 1; m < i; m++) {
                int current = result[m][j-1] + dp[m+1][i];
                if (current < result[i][j]) {
                    result[i][j] = current;
                }
            }
        }
    }

    printf("%d\n", result[n-1][k]);

    return 0;
}