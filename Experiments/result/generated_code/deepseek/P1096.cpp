#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    
    // 计算最少移动次数
    long long moves = pow(2, n + 1) - 2;
    
    printf("%lld\n", moves);
    
    return 0;
}