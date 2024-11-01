#include <stdio.h>
#include <string.h>

#define MOD 10007

int dp[100001][2];

void solve(int l, char *expr, int *result) {
    if (l == -1) {
        result[0] = 1;
        return;
    }
    if (dp[l][expr[l] == '(']) {
        memcpy(result, dp[l], sizeof(dp[l]));
        return;
    }
    int left[2] = {0}, right[2] = {0};
    solve(l - 1, expr, left);
    if (expr[l] == '+' || expr[l] == '*') {
        solve(l - 1, expr, right);
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (expr[l] == '+') {
                dp[l][i] = (dp[l][i] + ((left[i] ^ j) % MOD)) % MOD;
            } else if (expr[l] == '*') {
                dp[l][i] = (dp[l][i] + ((left[i] & j) % MOD)) % MOD;
            } else if (expr[l] == '(') {
                dp[l][i] = (dp[l][i] + (right[j] % MOD)) % MOD;
            }
        }
    }
    if (expr[l] != '(') {
        memcpy(result, dp[l], sizeof(dp[l]));
    }
}

int main() {
    int L;
    scanf("%d", &L);
    char expr[L + 1];
    scanf("%s", expr);
    int result[2] = {0};
    solve(L - 1, expr, result);
    printf("%d\n", result[0]);
    return 0;
}