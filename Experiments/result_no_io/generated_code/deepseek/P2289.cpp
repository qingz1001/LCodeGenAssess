#include <stdio.h>

long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

long long combination(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    // 计算从 (0, 0) 到 (m, n) 的路径数
    long long paths = combination(m + n, m);
    
    // 由于路径是对称的，所以乘以2
    paths *= 2;
    
    printf("%lld\n", paths);
    return 0;
}