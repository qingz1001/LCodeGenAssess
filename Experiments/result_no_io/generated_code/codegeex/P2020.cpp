#include <stdio.h>

typedef long long ll;

ll n, k, p;
ll f[1000005], g[1000005], h[1000005];

int main() {
    scanf("%lld%lld%lld", &n, &k, &p);

    // 初始化斐波那契数列的前两个数
    f[1] = 1;
    f[2] = 1;

    // 计算 f 数组，f[i] 表示第 i 个月的兔子数
    for (int i = 3; i <= k; i++) {
        f[i] = (f[i-1] + f[i-2]) % p;
    }

    // 初始化 g 数组，g[i] 表示 f[i] 除以 k 的余数
    for (int i = 1; i <= k; i++) {
        g[i] = f[i] % k;
    }

    // 初始化 h 数组，h[i] 表示 g 数组中第 i 个元素
    for (int i = 1; i <= k; i++) {
        h[i] = g[i];
    }

    // 通过循环卷积计算第 n 个月的兔子数
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            f[j] = (f[j] + h[i] * g[j]) % p;
        }
    }

    // 输出第 n 个月的兔子数除以 p 的余数
    printf("%lld\n", f[1]);

    return 0;
}