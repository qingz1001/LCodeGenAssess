#include <stdio.h>
#include <stdlib.h>

#define MOD 3

int main() {
    int n, m;
    scanf("%d", &n);
    int *binary = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &binary[i]);
    }
    scanf("%d", &m);

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)calloc(MOD, sizeof(int));
    }

    for (int i = 1; i <= n; i++) {
        dp[i][binary[i - 1]]++;
    }

    while (m--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int pos;
            scanf("%d", &pos);
            dp[pos][binary[pos - 1]]--;
            binary[pos - 1] = 1 - binary[pos - 1];
            dp[pos][binary[pos - 1]]++;
        } else {
            int l, r;
            scanf("%d %d", &l, &r);
            int count = 0;
            for (int i = 0; i < MOD; i++) {
                count += dp[r][i] - dp[l - 1][i];
            }
            printf("%d\n", count);
        }
    }

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    free(binary);

    return 0;
}