#include <stdio.h>
#include <math.h>

int main() {
    int k, x;
    scanf("%d %d", &k, &x);
    long long result = (long long)pow(10, k) + x;
    printf("%lld\n", result);
    return 0;
}