#include <stdio.h>
#include <stdlib.h>

#define MAX_S 100000
#define COIN_TYPES 4

long long dp[MAX_S + 1];

void preprocess(int c[COIN_TYPES]) {
    dp[0] = 1;
    for (int i = 0; i < COIN_TYPES; i++) {
        for (int j = c[i]; j <= MAX_S; j++) {
            dp[j] += dp[j - c[i]];
        }
    }
}

long long calculate_ways(int d[COIN_TYPES], int s, int c[COIN_TYPES]) {
    long long total_ways = dp[s];
    for (int mask = 1; mask < (1 << COIN_TYPES); mask++) {
        int sign = __builtin_popcount(mask) % 2 == 0 ? -1 : 1;
        int sum = 0;
        for (int i = 0; i < COIN_TYPES; i++) {
            if (mask & (1 << i)) {
                sum += c[i] * (d[i] + 1);
            }
        }
        if (s >= sum) {
            total_ways += sign * dp[s - sum];
        }
    }
    return total_ways;
}

int main() {
    int c[COIN_TYPES], n;
    scanf("%d %d %d %d %d", &c[0], &c[1], &c[2], &c[3], &n);

    preprocess(c);

    for (int i = 0; i < n; i++) {
        int d[COIN_TYPES], s;
        scanf("%d %d %d %d %d", &d[0], &d[1], &d[2], &d[3], &s);
        printf("%lld\n", calculate_ways(d, s, c));
    }

    return 0;
}