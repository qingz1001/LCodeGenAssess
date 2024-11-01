#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int W[MAXN], H[MAXN];

int main() {
    int N, L;
    scanf("%d%d", &N, &L);

    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &H[i], &W[i]);
    }

    long long dp[MAXN];
    dp[0] = 0;

    for (int i = 1; i <= N; i++) {
        int j = i - 1;
        long long current_width = 0, max_height = 0;

        while (j >= 0 && current_width + W[j + 1] <= L) {
            current_width += W[j + 1];
            max_height = (max_height > H[j + 1]) ? max_height : H[j + 1];
            dp[i] = (dp[i] < dp[j] + max_height) ? dp[i] : dp[j] + max_height;
            j--;
        }
    }

    printf("%lld\n", dp[N]);
    return 0;
}