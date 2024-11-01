#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000

int N;
int prices[MAX_N];
int dp[MAX_N];
long long count[MAX_N];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &prices[i]);
    }

    int max_buys = 0;
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
        if (dp[i] > max_buys) {
            max_buys = dp[i];
        }
    }

    long long total_count = 0;
    for (int i = 0; i < N; i++) {
        if (dp[i] == max_buys) {
            total_count += count[i];
        }
    }

    printf("%d %lld\n", max_buys, total_count);

    return 0;
}