#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_LEN 400

int n;
char s[MAX_N][MAX_LEN];
int len[MAX_N];
int dp[MAX_LEN][MAX_LEN];
int pre[MAX_LEN][MAX_LEN];
char res[MAX_LEN * MAX_N];

int cmp(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
        len[i] = strlen(s[i]);
    }

    qsort(s, n, sizeof(char *), cmp);

    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    }

    for (int l = 2; l <= n; l++) {
        for (int i = 0; i + l - 1 < n; i++) {
            int j = i + l - 1;
            for (int k = i; k < j; k++) {
                if (dp[i][k] + dp[k + 1][j] <= dp[i][j]) {
                    dp[i][j] = dp[i][k] + dp[k + 1][j];
                    pre[i][j] = k;
                }
            }
            for (int k = 0; k < i; k++) {
                if (strcmp(s[k], s[j]) == 0) {
                    dp[i][j] = 0;
                    pre[i][j] = -1;
                    break;
                }
            }
        }
    }

    int min_len = dp[0][n - 1];
    int pos = pre[0][n - 1];

    int len_res = 0;
    int p = 0;
    while (pos != -1) {
        for (int i = 0; i < len[pos]; i++) {
            res[p++] = s[pos][i];
        }
        len_res += len[pos];
        pos = pre[i][pos];
    }

    for (int i = len[pos]; i < len[n - 1]; i++) {
        res[p++] = s[n - 1][i];
    }
    len_res += len[n - 1] - len[pos];

    printf("%d\n", len_res);
    for (int i = 0; i < len_res; i++) {
        printf("%c", res[i]);
    }
    printf("\n");

    return 0;
}