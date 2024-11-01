#include <stdio.h>
#include <string.h>

#define MOD 10007
#define MAXN 100005

char expr[MAXN];
int dp[MAXN][2];
int stack[MAXN], top;

int main() {
    int L, i;
    scanf("%d", &L);
    scanf("%s", expr);

    dp[0][0] = 1;
    dp[0][1] = 1;

    for (i = 1; i <= L; i++) {
        if (expr[i-1] == '+') {
            dp[i][0] = (dp[i-1][0] * dp[i-1][0] + dp[i-1][1] * dp[i-1][1]) % MOD;
            dp[i][1] = (dp[i-1][0] * dp[i-1][1] + dp[i-1][1] * dp[i-1][0] + dp[i-1][1] * dp[i-1][1]) % MOD;
        } else if (expr[i-1] == '*') {
            dp[i][0] = (dp[i-1][0] * dp[i-1][0] + dp[i-1][0] * dp[i-1][1] + dp[i-1][1] * dp[i-1][0]) % MOD;
            dp[i][1] = (dp[i-1][1] * dp[i-1][1]) % MOD;
        } else if (expr[i-1] == '(') {
            stack[top++] = i;
        } else if (expr[i-1] == ')') {
            int j = stack[--top];
            dp[i][0] = dp[j-1][0] * dp[i-1][0] + dp[j-1][1] * dp[i-1][1];
            dp[i][1] = dp[j-1][0] * dp[i-1][1] + dp[j-1][1] * dp[i-1][0] + dp[j-1][1] * dp[i-1][1];
            dp[i][0] %= MOD;
            dp[i][1] %= MOD;
        }
    }

    printf("%d\n", dp[L][0]);
    return 0;
}