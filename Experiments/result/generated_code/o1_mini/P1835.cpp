#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int main(){
    unsigned long long L, R;
    scanf("%llu %llu", &L, &R);
    
    unsigned long long limit = sqrt((double)R) + 1;
    bool *is_prime_small = calloc(limit + 1, sizeof(bool));
    for(unsigned long long i=0;i<=limit;i++) is_prime_small[i] = true;
    is_prime_small[0] = is_prime_small[1] = false;
    for(unsigned long long i=2;i<=limit;i++){
        if(is_prime_small[i]){
            for(unsigned long long j=i*i; j<=limit; j+=i){
                is_prime_small[j] = false;
            }
        }
    }
    
    unsigned long long size = R - L +1;
    bool *is_prime = calloc(size, sizeof(bool));
    for(unsigned long long i=0;i<size;i++) is_prime[i] = true;
    
    for(unsigned long long i=2;i<=limit;i++){
        if(is_prime_small[i]){
            unsigned long long start = (L + i -1)/i * i;
            if(start < i*i) start = i*i;
            for(unsigned long long j=start; j<=R; j+=i){
                if(j >= L){
                    is_prime[j - L] = false;
                }
            }
        }
    }
    
    if(L ==1){
        is_prime[0] = false;
    }
    
    unsigned long long count =0;
    for(unsigned long long i=0;i<size;i++) if(is_prime[i]) count++;
    printf("%llu\n", count);
    
    free(is_prime_small);
    free(is_prime);
    return 0;
}