#include <stdio.h>
#include <math.h>

#define MAX_N 1000000000

long long sum[MAX_N + 1];
double f[MAX_N + 1];

int main() {
    int T;
    scanf("%d", &T);

    // 预处理
    for (long long i = 2; i <= MAX_N; i++) {
        long long val = (long long)pow(i, 0.5);
        long long g = 0;
        for (long long j = 2; j <= val; j++) {
            if (i % (j * j) == 0) {
                g++;
                long long k = j * j;
                while (i % k == 0) {
                    k *= j;
                    g++;
                }
            }
        }
        sum[i] = sum[i - 1] + g;
        f[i] = f[i - 1] + (double)sum[i] / i;
    }

    // 处理每个询问
    while (T--) {
        long long n;
        scanf("%lld", &n);
        if (n > MAX_N) {
            // 对于较大的n，使用线性插值
            printf("%.14lf\n", f[MAX_N] + (f[n] - f[MAX_N]) * MAX_N / n);
        } else {
            printf("%.14lf\n", f[n]);
        }
    }

    return 0;
}