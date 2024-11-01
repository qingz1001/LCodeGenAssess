#include <stdio.h>
#include <string.h>

#define MOD 10000

int n, t;
int names[50][100001];
int lengths[50];

void compute_average_singing_time(int n, int t, int names[50][100001], int lengths[50]) {
    for (int i = 0; i < t; i++) {
        int m = lengths[i];
        int name[m];
        for (int j = 0; j < m; j++) {
            name[j] = names[i][j];
        }

        int dp[m + 1];
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;

        for (int j = 1; j <= m; j++) {
            dp[j] = (dp[j - 1] * n) % MOD;
        }

        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < j; k++) {
                if (memcmp(name, name + j - k, k * sizeof(int)) == 0) {
                    dp[j] = (dp[j] + dp[j - k]) % MOD;
                }
            }
        }

        printf("%04d\n", dp[m]);
    }
}

int main() {
    scanf("%d %d", &n, &t);
    for (int i = 0; i < t; i++) {
        scanf("%d", &lengths[i]);
        for (int j = 0; j < lengths[i]; j++) {
            scanf("%d", &names[i][j]);
        }
    }

    compute_average_singing_time(n, t, names, lengths);

    return 0;
}