#include <stdio.h>

int main() {
    unsigned long long x, n;
    scanf("%llu %llu", &x, &n);
    
    unsigned long long infected = 1; // 初始只有一个禽兽被传染
    
    for (unsigned long long i = 0; i < n; i++) {
        infected += infected * x;
    }
    
    printf("%llu\n", infected);
    
    return 0;
}