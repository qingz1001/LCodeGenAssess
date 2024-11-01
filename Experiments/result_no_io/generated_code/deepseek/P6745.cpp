#include <stdio.h>
#include <math.h>

int main() {
    int k;
    long long x;
    scanf("%d %lld", &k, &x);
    
    long long result = (long long)pow(10, k) + x;
    printf("%lld\n", result);
    
    return 0;
}