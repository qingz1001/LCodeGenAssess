#include <stdio.h>
#include <string.h>

#define MOD 10007
#define MAXN 100005

char expr[MAXN];
int dp[MAXN][2], L;

int calc(int a, int b, char op) {
    if (op == '+') return (a | b);
    return (a & b);
}

void solve() {
    int i, j, k;
    memset(dp, 0, sizeof(dp));
    
    for (i = L; i >= 0; i--) {
        if (expr[i] == ')' || expr[i] == '\0') {
            dp[i][0] = dp[i][1] = 1;
        } else if (expr[i] == '(') {
            dp[i][0] = dp[i+1][0];
            dp[i][1] = dp[i+1][1];
        } else {
            char op = expr[i];
            for (j = 0; j < 2; j++) {
                for (k = 0; k < 2; k++) {
                    int res = calc(j, k, op);
                    dp[i][res] = (dp[i][res] + dp[i+1][j] * dp[i+2][k]) % MOD;
                }
            }
        }
    }
    
    printf("%d\n", dp[0][0]);
}

int main() {
    scanf("%d", &L);
    scanf("%s", expr);
    solve();
    return 0;
}