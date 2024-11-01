#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_H 20

long long dp[MAX_N+1][1<<MAX_N];
int n, k, h;
int color[MAX_H];

long long dfs(int row, int state) {
    if (row == n) return k == 0;
    if (dp[row][state] != -1) return dp[row][state];

    long long ans = 0;
    for (int new_state = 0; new_state < (1<<n); new_state++) {
        if ((new_state & state) || (new_state & (new_state << 1))) continue;
        int count = __builtin_popcount(new_state);
        if (count > k) continue;
        k -= count;
        ans += dfs(row+1, new_state);
        k += count;
    }

    return dp[row][state] = ans;
}

long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    scanf("%d %d %d", &n, &k, &h);
    
    int total = 0;
    for (int i = 0; i < h; i++) {
        scanf("%d", &color[i]);
        total += color[i];
    }

    if (total != k) {
        printf("0\n");
        return 0;
    }

    memset(dp, -1, sizeof(dp));
    long long arrangements = dfs(0, 0);

    long long denominator = 1;
    for (int i = 0; i < h; i++) {
        denominator *= factorial(color[i]);
    }

    printf("%lld\n", arrangements / denominator);

    return 0;
}