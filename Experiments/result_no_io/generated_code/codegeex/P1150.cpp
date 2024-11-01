#include <stdio.h>

int main() {
    long long n, k, total_cigarettes, total_tobaccos, remaining_tobaccos;
    
    while (scanf("%lld %lld", &n, &k) != EOF) {
        total_cigarettes = n;
        total_tobaccos = n;
        remaining_tobaccos = 0;
        
        while (total_tobaccos >= k) {
            remaining_tobaccos = total_tobaccos % k;
            total_cigarettes += total_tobaccos / k;
            total_tobaccos = total_tobaccos / k + remaining_tobaccos;
        }
        
        printf("%lld\n", total_cigarettes);
    }
    
    return 0;
}