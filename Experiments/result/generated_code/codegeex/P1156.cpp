#include <stdio.h>
#include <string.h>

int d, g;
int t[105], f[105], h[105];

int main() {
    scanf("%d %d", &d, &g);
    for (int i = 1; i <= g; i++) {
        scanf("%d %d %d", &t[i], &f[i], &h[i]);
    }

    int dp[105][1005] = {0};
    int ans = 0;

    for (int i = 1; i <= g; i++) {
        for (int j = d; j >= 0; j--) {
            for (int k = 10; k >= 0; k--) {
                if (dp[i-1][k] != 0) {
                    if (j + h[i] >= d) {
                        ans = t[i];
                        goto out;
                    } else if (k + f[i] >= t[i] - t[i-1]) {
                        dp[i][t[i] - t[i-1]] = j + h[i];
                    }
                }
            }
        }
    }

    for (int i = 10; i >= 0; i--) {
        if (dp[g][i] >= d) {
            ans = i;
            break;
        }
    }

out:
    printf("%d\n", ans);
    return 0;
}