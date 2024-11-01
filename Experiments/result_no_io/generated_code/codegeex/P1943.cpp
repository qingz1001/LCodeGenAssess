#include <stdio.h>

int main() {
    long long n;
    scanf("%lld", &n);
    
    double expected_local_maxima = 0.0;
    
    // 计算期望值
    for (long long i = 1; i <= n; i++) {
        expected_local_maxima += (double)i / (i + 1);
    }
    
    // 输出结果，保留八位小数
    printf("%.8lf\n", expected_local_maxima);
    
    return 0;
}