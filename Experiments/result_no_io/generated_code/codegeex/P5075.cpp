#include <stdio.h>

#define MOD 255

long long m, p, a, o, s, u;
long long dp[10010][11];

int main() {
    // 读取输入
    scanf("%lld %lld %lld %lld %lld %lld", &m, &p, &a, &o, &s, &u);

    // 初始化dp数组
    dp[0][0] = 1;

    // 动态规划计算
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= 10; j++) {
            for (int k = 0; k <= a && k * i <= m; k++) {
                long long val = (o * k * k + s * k + u) % p;
                dp[i][j] = (dp[i][j] + dp[i - k * i][j - 1] * val) % p;
            }
        }
    }

    // 计算结果
    long long result = 0;
    for (int i = 0; i <= 10; i++) {
        result = (result + dp[m][i]) % p;
    }

    // 输出结果
    printf("%lld\n", result);

    return 0;
}