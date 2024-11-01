#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int height;
    int width;
} Book;

Book books[MAX_N];
int dp[MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
    }

    dp[0] = books[0].height;
    int cur_width = books[0].width;
    int cur_height = books[0].height;

    for (int i = 1; i < N; i++) {
        if (cur_width + books[i].width <= L) {
            cur_width += books[i].width;
            cur_height = max(cur_height, books[i].height);
            dp[i] = dp[i-1];
        } else {
            cur_width = books[i].width;
            cur_height = books[i].height;
            dp[i] = dp[i-1] + cur_height;
        }
    }

    printf("%d\n", dp[N-1]);

    return 0;
}