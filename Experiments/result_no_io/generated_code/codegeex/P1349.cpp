#include <stdio.h>

long long p, q, a1, a2, n, m;

int main() {
    // 读取输入
    scanf("%lld %lld %lld %lld %lld %lld", &p, &q, &a1, &a2, &n, &m);

    // 如果n为1，直接输出a1对m取模的结果
    if (n == 1) {
        printf("%lld\n", a1 % m);
    }
    // 如果n为2，直接输出a2对m取模的结果
    else if (n == 2) {
        printf("%lld\n", a2 % m);
    }
    // 否则计算数列的第n项
    else {
        long long an = 0;
        for (int i = 3; i <= n; i++) {
            an = (p * a1 + q * a2) % m;
            a1 = a2;
            a2 = an;
        }
        printf("%lld\n", an);
    }

    return 0;
}