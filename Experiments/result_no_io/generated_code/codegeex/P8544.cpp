#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

long long a[500005], b[500005];
long long n, m, t;

// 计算最小值
long long min(long long x, long long y) {
    return x < y ? x : y;
}

// 计算最大值
long long max(long long x, long long y) {
    return x > y ? x : y;
}

// 计算两个数的乘积并取模
long long mul(long long x, long long y) {
    return (x * y) % MOD;
}

// 计算两个数的和并取模
long long add(long long x, long long y) {
    return (x + y) % MOD;
}

int main() {
    // 读取输入
    scanf("%lld %lld %lld", &n, &m, &t);
    for (long long i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    for (long long i = 0; i < m; i++) {
        scanf("%lld", &b[i]);
    }

    // 计算矩阵A的每个元素
    long long A[500005][500005];
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            A[i][j] = mul(a[i], b[j]);
        }
    }

    // 计算f(B)的最小值
    long long fB = 0;
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < t; j++) {
            // 构造矩阵B的每列
            long long x = (j % 2 == 0) ? 1 : m;
            long long y = (j % 2 == 0) ? m : 1;

            // 计算f(B)的贡献
            for (long long k = min(x, y); k <= max(x, y); k++) {
                fB = add(fB, mul(A[i][k-1], k));
            }
        }
    }

    // 输出结果
    printf("%lld\n", fB);
    return 0;
}