#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        long long a, c;
        scanf("%lld %lld", &a, &c);
        
        long long b = -1;
        
        // 遍历所有可能的 n 和 m 的组合
        for (long long n = 1; n * n <= a; n++) {
            if (a % n == 0) {
                long long m1 = a / n;
                if (c * m1 == (a / n) / m1) {
                    b = a / n;
                    break;
                }
                if (c * n == (a / n) / n) {
                    b = a / n;
                    break;
                }
            }
        }
        
        printf("%lld\n", b);
    }
    
    return 0;
}