#include <stdio.h>
#include <string.h>

#define MAXN 1000000

long long n, k, p;
long long a[MAXN + 5];

int main() {
    // 读取输入
    scanf("%lld %lld %lld", &n, &k, &p);

    // 初始化斐波那契数列的前两个数
    a[0] = 1 % p;
    a[1] = 1 % p;

    // 计算斐波那契数列直到第 n 项
    for (int i = 2; i <= n; i++) {
        a[i] = (a[i - 1] + a[i - 2]) % p;
    }

    // 计算第 n 个月的兔子对数除以 k 的余数
    long long result = a[n] % k;

    // 输出结果
    printf("%lld\n", result);

    return 0;
}