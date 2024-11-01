#include <stdio.h>
#include <math.h>

int main() {
    long long n;
    scanf("%lld", &n);
    
    long long i;
    for (i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            printf("%lld\n", n / i);
            break;
        }
    }
    
    return 0;
}