#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000

int n;
int prices[MAX_N];
int dp[MAX_N];
int count[MAX_N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    int max_buys = 0;
    long long total_ways = 0;

    for (int i = 0; i < n; i++) {
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
            total_ways = count[i];
        } else if (dp[i] == max_buys) {
            total_ways += count[i];
        }
    }

    printf("%d %lld\n", max_buys, total_ways);

    return 0;
}