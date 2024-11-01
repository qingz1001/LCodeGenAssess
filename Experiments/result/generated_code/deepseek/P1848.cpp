#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100000

typedef struct {
    int height;
    int width;
} Book;

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);

    Book books[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
    }

    int dp[MAXN];
    int max_height[MAXN];
    int width_sum[MAXN];

    dp[0] = books[0].height;
    max_height[0] = books[0].height;
    width_sum[0] = books[0].width;

    for (int i = 1; i < N; i++) {
        dp[i] = dp[i - 1] + books[i].height;
        max_height[i] = books[i].height;
        width_sum[i] = books[i].width;

        int current_width = books[i].width;
        int current_max_height = books[i].height;

        for (int j = i - 1; j >= 0; j--) {
            current_width += books[j].width;
            if (current_width > L) break;
            current_max_height = current_max_height > books[j].height ? current_max_height : books[j].height;
            if (j > 0) {
                dp[i] = min(dp[i], dp[j - 1] + current_max_height);
            } else {
                dp[i] = min(dp[i], current_max_height);
            }
        }
    }

    printf("%d\n", dp[N - 1]);

    return 0;
}