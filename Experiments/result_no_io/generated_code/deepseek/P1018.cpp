#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 41
#define MAXK 6

long long dp[MAXN][MAXK];
char num[MAXN];

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long str_to_int(char *str, int start, int end) {
    long long result = 0;
    for (int i = start; i <= end; i++) {
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    scanf("%s", num);

    // Initialize dp array
    for (int i = 0; i < N; i++) {
        dp[i][0] = str_to_int(num, 0, i);
    }

    // Fill dp array
    for (int k = 1; k <= K; k++) {
        for (int i = k; i < N; i++) {
            for (int j = k - 1; j < i; j++) {
                dp[i][k] = max(dp[i][k], dp[j][k - 1] * str_to_int(num, j + 1, i));
            }
        }
    }

    // The result is the maximum product with K multiplications
    printf("%lld\n", dp[N - 1][K]);

    return 0;
}