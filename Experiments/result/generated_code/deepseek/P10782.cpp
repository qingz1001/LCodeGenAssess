#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        long long a, c;
        scanf("%lld %lld", &a, &c);
        
        long long b = -1;
        for (long long n = 1; n * n <= a; n++) {
            if (a % n == 0) {
                long long m1 = a / n;
                long long m2 = n;
                
                if ((a / m1) / m1 == c) {
                    b = a / m1;
                    break;
                }
                
                if ((a / m2) / m2 == c) {
                    b = a / m2;
                    break;
                }
            }
        }
        
        printf("%lld\n", b);
    }
    
    return 0;
}