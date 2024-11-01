#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100000

int N, L;
int H[MAXN], W[MAXN];
int dp[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &N, &L);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &H[i], &W[i]);
    }

    for (int i = 0; i < N; i++) {
        dp[i] = INT_MAX;
    }

    dp[0] = H[0];

    for (int i = 1; i < N; i++) {
        int max_height = H[i];
        int total_width = W[i];
        for (int j = i; j >= 0; j--) {
            if (total_width > L) break;
            dp[i] = min(dp[i], (j > 0 ? dp[j - 1] : 0) + max_height);
            if (j > 0) {
                max_height = max_height > H[j - 1] ? max_height : H[j - 1];
                total_width += W[j - 1];
            }
        }
    }

    printf("%d\n", dp[N - 1]);

    return 0;
}