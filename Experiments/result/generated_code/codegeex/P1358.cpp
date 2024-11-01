#include <stdio.h>

// 计算阶乘并取模
int factorial(int n, int mod) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result = (result * i) % mod;
    }
    return result;
}

// 计算组合数 C(n, k) 并取模
int combination(int n, int k, int mod) {
    if (k > n) return 0;
    int numerator = factorial(n, mod);
    int denominator = (factorial(k, mod) * factorial(n - k, mod)) % mod;
    return (numerator * factorial(denominator, mod)) % mod;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[100];
    int sum = 0;
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    
    if (sum > n) {
        printf("0\n");
        return 0;
    }
    
    int result = combination(n, sum, 10007);
    for (int i = 0; i < m; i++) {
        result = (result * combination(n - sum + i, a[i], 10007)) % 10007;
        sum -= a[i];
    }
    
    printf("%d\n", result);
    return 0;
}