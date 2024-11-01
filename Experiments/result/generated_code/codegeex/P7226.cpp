#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    
    long long X = 0;
    for (int i = 0; i < n; i++) {
        int q;
        scanf("%d", &q);
        
        int p = q % 10;  // 提取个位数
        int num = q / 10;  // 提取前面的数字
        
        X += pow(num, p);  // 计算 num^p 并累加到 X
    }
    
    printf("%lld\n", X);
    
    return 0;
}