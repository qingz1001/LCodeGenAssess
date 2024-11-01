#include <stdio.h>
#include <string.h>

#define MAX_N 25
#define MAX_H 16
#define INF 0x3f3f3f3f

int n, H;
int f[MAX_N], d[MAX_N], t[MAX_N];
int dp[MAX_N][MAX_H * 12 + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    scanf("%d", &H);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &f[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &t[i]);
    }

    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;

    int totalTime = H * 12;  // 转换为5分钟为单位
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= totalTime; j++) {
            if (dp[i][j] == -1) continue;

            // 不在当前湖钓鱼，直接前往下一个湖
            if (i < n - 1 && j + t[i] <= totalTime) {
                dp[i + 1][j + t[i]] = max(dp[i + 1][j + t[i]], dp[i][j]);
            }

            // 在当前湖钓鱼
            int time = 0;
            int fish = 0;
            int cur = f[i];
            while (cur > 0 && j + time <= totalTime) {
                fish += cur;
                dp[i][j + time] = max(dp[i][j + time], dp[i][j] + fish);
                time++;
                cur = max(0, cur - d[i]);
            }
        }
    }

    int result = 0;
    for (int j = 0; j <= totalTime; j++) {
        result = max(result, dp[n - 1][j]);
    }

    printf("%d\n", result);

    return 0;
}