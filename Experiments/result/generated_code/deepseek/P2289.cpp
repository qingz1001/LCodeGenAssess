#include <stdio.h>

// 计算组合数 C(n, k)
long long comb(int n, int k) {
    if (k > n - k) k = n - k; // 利用组合数的对称性
    long long res = 1;
    for (int i = 0; i < k; i++) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    // 计算从 (0,0) 到 (m,n) 的最短路径数
    // 最短路径需要走 m+n 步，其中 m 步向下，n 步向右
    long long routes = comb(m + n, m);
    
    // 由于路径是对称的，所以结果需要乘以2
    routes *= 2;
    
    printf("%lld\n", routes);
    return 0;
}