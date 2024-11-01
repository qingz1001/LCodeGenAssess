#include <stdio.h>
#include <string.h>

#define MOD 1000000009

int main() {
    char s[500005];
    scanf("%s", s);
    int n = strlen(s);
    int f[500005] = {0}, g[500005] = {0}, h[500005] = {0};

    // 初始化
    f[0] = 1;
    g[0] = 1;

    // 动态规划
    for (int i = 1; i < n; i++) {
        if (s[i] == 'B') {
            f[i] = (f[i-1] + g[i-1]) % MOD;
            g[i] = h[i-1];
        } else if (s[i] == 'W') {
            h[i] = (f[i-1] + g[i-1] + h[i-1]) % MOD;
        } else {
            f[i] = (f[i-1] + g[i-1]) % MOD;
            g[i] = h[i-1];
            h[i] = (f[i-1] + g[i-1] + h[i-1]) % MOD;
        }
    }

    // 计算最终结果
    int result = (f[n-1] + g[n-1] + h[n-1]) % MOD;
    printf("%d\n", result);

    return 0;
}