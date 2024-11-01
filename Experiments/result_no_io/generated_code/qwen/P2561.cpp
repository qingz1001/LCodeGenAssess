#include <stdio.h>
#include <string.h>

#define MAXN 21
#define MAXS 400

char dp[MAXN][MAXS];
int n;

void preprocess() {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i * 2; ++j) {
            if (dp[i][j]) {
                if (j + 1 <= i * 2) dp[i + 1][j + 1] += dp[i][j];
                if (j + 2 <= i * 2) dp[i + 1][j + 2] += dp[i][j];
            }
        }
    }
}

void print_result(int len) {
    for (int i = len - 1; i >= 0; --i) printf("%d", dp[n][i]);
    printf("\n");
}

int main() {
    scanf("%d", &n);
    preprocess();
    int len = 0;
    while (dp[n][len]) len++;
    print_result(len);
    return 0;
}