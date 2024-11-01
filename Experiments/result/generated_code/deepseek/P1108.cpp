#include <stdio.h>
#include <stdlib.h>

#define MAXN 5000

int prices[MAXN];
int dp[MAXN];
int count[MAXN];

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &prices[i]);
    }

    int max_len = 1;
    int max_count = 0;

    for (int i = 0; i < N; i++) {
        dp[i] = 1;
        count[i] = 1;
        for (int j = 0; j < i; j++) {
            if (prices[j] > prices[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    count[i] = count[j];
                } else if (dp[j] + 1 == dp[i]) {
                    count[i] += count[j];
                }
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            max_count = count[i];
        } else if (dp[i] == max_len) {
            max_count += count[i];
        }
    }

    printf("%d %d\n", max_len, max_count);

    return 0;
}