#include <stdio.h>

#define MOD 1000000007

int main() {
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);

    // 计算n个顶点的置换数，即n!
    long long factorial_n = 1;
    for (int i = 1; i <= n; i++) {
        factorial_n = (factorial_n * i) % p;
    }

    // 计算n个顶点的不同构图的个数
    long long result = factorial_n;
    for (int i = 1; i <= n; i++) {
        result = (result * i) % p;
    }

    // 输出结果
    printf("%lld\n", result);

    return 0;
}