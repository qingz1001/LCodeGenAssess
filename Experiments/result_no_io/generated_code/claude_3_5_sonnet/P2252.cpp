#include <stdio.h>
#include <math.h>

int isWinningPosition(long long a, long long b) {
    if (a > b) {
        long long temp = a;
        a = b;
        b = temp;
    }
    
    double phi = (1 + sqrt(5)) / 2;
    long long k = (long long)((b - a) / phi);
    
    return (a == k);
}

int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    
    if (isWinningPosition(a, b)) {
        printf("0\n");
    } else {
        printf("1\n");
    }
    
    return 0;
}