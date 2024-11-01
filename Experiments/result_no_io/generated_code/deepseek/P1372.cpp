#include <stdio.h>

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    
    // 最大的默契值是 k 本身，因为 k 个人的最大公约数是 k
    printf("%lld\n", k);
    
    return 0;
}