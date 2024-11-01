#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    // 最大的默契值是 n / k 的最大整数部分
    int max_gcd = n / k;
    
    printf("%d\n", max_gcd);
    
    return 0;
}