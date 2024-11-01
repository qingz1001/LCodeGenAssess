#include <stdio.h>

int main() {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);

    // 计算第一类斯特林数（Stirling numbers of the first kind）
    long long stirling[n+1][n+1];
    for (int i = 0; i <= n; i++) {
        stirling[i][0] = stirling[i][i] = 1;
        for (int j = 1; j < i; j++) {
            stirling[i][j] = (stirling[i-1][j-1] + stirling[i-1][j]) % p;
        }
    }

    // 计算第二类斯特林数（Stirling numbers of the second kind）
    long long stirling2[n+1][n+1];
    for (int i = 0; i <= n; i++) {
        stirling2[i][0] = stirling2[i][i] = 1;
        for (int j = 1; j < i; j++) {
            stirling2[i][j] = (stirling2[i-1][j] + stirling2[i-1][j-1]) % p;
        }
    }

    // 计算n个点的n阶无向完全图的同构图数
    long long result = 0;
    for (int i = 0; i <= n; i++) {
        result = (result + stirling[n][i] * stirling2[n-i][n-i] % p) % p;
    }

    // 计算最终结果
    long long answer = result * m % p * m % p;

    printf("%lld\n", answer);
    return 0;
}