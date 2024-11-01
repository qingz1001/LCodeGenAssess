#include <stdio.h>
#include <math.h>

int main() {
    long long r, count = 0;
    scanf("%lld", &r);
    
    for (long long x = -r; x <= r; x++) {
        long long y_squared = r * r - x * x;
        long long y = sqrt(y_squared);
        
        if (y * y == y_squared) {
            count += (y % 2 == 0 ? 4 : 4);
        }
    }
    
    printf("%lld\n", count);
    return 0;
}