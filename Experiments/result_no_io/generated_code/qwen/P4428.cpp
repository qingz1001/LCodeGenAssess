#include <stdio.h>
#include <stdlib.h>

#define MOD 3

int main() {
    int n, m;
    scanf("%d", &n);
    char *binary = (char *)malloc((n + 1) * sizeof(char));
    for (int i = 1; i <= n; ++i) {
        scanf(" %c", &binary[i]);
    }
    scanf("%d", &m);

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; ++i) {
        dp[i] = (int *)calloc(MOD, sizeof(int));
    }

    for (int i = 1; i <= n; ++i) {
        dp[i][binary[i] - '0']++;
    }

    for (int i = 1; i <= n; ++i) {
        dp[i][(dp[i - 1][0] + dp[i - 1][1]) % MOD]++;
    }

    while (m--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int pos;
            scanf("%d", &pos);
            dp[pos][binary[pos] - '0']--;
            binary[pos] = (binary[pos] == '0') ? '1' : '0';
            dp[pos][binary[pos] - '0']++;
        } else {
            int l, r;
            scanf("%d %d", &l, &r);
            int sum = 0;
            for (int i = 0; i < MOD; ++i) {
                sum += dp[r][i];
                if (l > 1) {
                    sum -= dp[l - 1][i];
                }
            }
            printf("%d\n", sum);
        }
    }

    free(binary);
    for (int i = 0; i <= n; ++i) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}