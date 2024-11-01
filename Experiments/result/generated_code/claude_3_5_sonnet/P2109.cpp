#include <stdio.h>
#include <string.h>
#define MOD 65521
#define MAXN 1005

int k, n;
int f[MAXN][MAXN];

int main() {
    scanf("%d %d", &k, &n);
    
    // 初始化边界条件
    f[1][0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i][i-1] = 1;
    }
    
    // 动态规划
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i-1; j++) {
            for (int p = 1; p <= k && i-p > j; p++) {
                f[i][j] = (f[i][j] + f[i-p][j]) % MOD;
            }
        }
    }
    
    // 计算结果
    int result = 0;
    for (int j = 0; j < n; j++) {
        result = (result + f[n][j]) % MOD;
    }
    
    printf("%d\n", result);
    
    return 0;
}