#include <stdio.h>
#include <string.h>

int n;
char s[25][25];
int dp[25][25][1 << 20];
int pre[25][25][1 << 20];
char res[25][25][1 << 20];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
    }

    int minlen = 1 << 30;
    int minid = -1;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                for (int j = 0; j < n; j++) {
                    if (i == j || !(mask & (1 << j))) continue;
                    for (int k = 0; k < n; k++) {
                        if (k == i || k == j || !(mask & (1 << k))) continue;
                        int len = strlen(s[i]) + strlen(s[j]);
                        if (dp[i][j][mask] > dp[k][i][mask ^ (1 << j)] + len) {
                            dp[i][j][mask] = dp[k][i][mask ^ (1 << j)] + len;
                            pre[i][j][mask] = k;
                            strcpy(res[i][j][mask], res[k][i][mask ^ (1 << j)]);
                            strcat(res[i][j][mask], s[j]);
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (dp[i][i][mask] < minlen) {
                    minlen = dp[i][i][mask];
                    minid = i;
                }
            }
        }
    }

    printf("%d\n", minlen);
    printf("%s\n", res[minid][minid][(1 << n) - 1]);

    return 0;
}