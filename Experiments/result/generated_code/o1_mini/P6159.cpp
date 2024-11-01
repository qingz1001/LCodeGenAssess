#include <stdio.h>
#include <stdint.h>

int main(){
    int64_t n, p, k;
    scanf("%lld %lld %lld", &n, &p, &k);
    int64_t t = (p * k) % n;
    printf("%lld\n", t);
    return 0;
}