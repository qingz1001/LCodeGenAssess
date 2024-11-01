#include <stdio.h>

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    
    long long total_cigarettes = n;
    long long butts = n;
    
    while (butts >= k) {
        long long new_cigarettes = butts / k;
        total_cigarettes += new_cigarettes;
        butts = butts % k + new_cigarettes;
    }
    
    printf("%lld\n", total_cigarettes);
    return 0;
}