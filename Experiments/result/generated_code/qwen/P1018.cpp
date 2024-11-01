#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

long long maxProduct(int N, int K, char *num) {
    long long dp[N + 1][K + 1];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 1;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            if (dp[i - 1][j] != -1) {
                long long current = 0;
                for (int l = i; l >= 1; l--) {
                    current = current * 10 + num[l - 1] - '0';
                    if (j == 0 && l == 1) {
                        dp[i][j] = MAX(dp[i][j], current);
                    } else if (j > 0 && l >= 1) {
                        dp[i][j] = MAX(dp[i][j], dp[l - 1][j - 1] * current);
                    }
                }
            }
        }
    }

    return dp[N][K];
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    getchar(); // consume newline character left in the buffer
    char *num = (char *)malloc((N + 1) * sizeof(char));
    fgets(num, N + 2, stdin); // read the string with newline at the end

    long long result = maxProduct(N, K, num);

    printf("%lld\n", result);

    free(num);
    return 0;
}