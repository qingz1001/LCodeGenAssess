#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    int prices[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &prices[i]);
    }

    int dp[N];
    int cnt[N];
    dp[0] = 1;
    cnt[0] = 1;

    for (int i = 1; i < N; i++) {
        dp[i] = 1;
        cnt[i] = 1;
        for (int j = 0; j < i; j++) {
            if (prices[j] > prices[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                } else if (dp[j] + 1 == dp[i]) {
                    cnt[i] += cnt[j];
                }
            }
        }
    }

    int max_buy = 0;
    int max_count = 0;
    for (int i = 0; i < N; i++) {
        if (dp[i] > max_buy) {
            max_buy = dp[i];
            max_count = cnt[i];
        } else if (dp[i] == max_buy) {
            max_count += cnt[i];
        }
    }

    printf("%d %d\n", max_buy, max_count);

    return 0;
}