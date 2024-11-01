#include <stdio.h>
#include <string.h>

#define N 110
#define M 60010

int dp[N][M], maxn;
int n = 1;

int dfs(int now, int time, int *a) {
    if (time > maxn) return 0;
    if (dp[now][time] != -1) return dp[now][time];
    if (a[now] == 0) {
        int x = dfs(now * 2, time + a[now * 2], a);
        int y = dfs(now * 2 + 1, time + a[now * 2 + 1], a);
        dp[now][time] = x > y ? x : y;
    } else {
        dp[now][time] = dfs(now * 2, time + a[now * 2], a) + dfs(now * 2 + 1, time + a[now * 2 + 1], a) + a[now] / 5;
    }
    return dp[now][time];
}

int main() {
    memset(dp, -1, sizeof(dp));
    scanf("%d", &maxn);
    maxn -= 1;
    while (~scanf("%d", &dp[n][0])) {
        scanf("%d", &dp[n][1]);
        if (dp[n][1] == 0) {
            n *= 2;
        } else {
            n++;
        }
    }
    printf("%d", dfs(1, 0, dp));
    return 0;
}