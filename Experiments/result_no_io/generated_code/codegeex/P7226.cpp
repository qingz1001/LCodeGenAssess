#include <stdio.h>
#include <math.h>

long long q[11];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &q[i]);
    }
    
    long long X = 0;
    for (int i = 1; i <= n; i++) {
        long long num = q[i] / 10;
        long long p = q[i] % 10;
        X += pow(num, p);
    }
    
    printf("%lld\n", X);
    return 0;
}