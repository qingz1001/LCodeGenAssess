#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long a;
    long long b;
} fib;

// Fast doubling method to compute F(n) mod p
fib fib_fast_doubling(long long n, long long p) {
    if (n == 0) {
        fib res = {0, 1};
        return res;
    }
    fib half = fib_fast_doubling(n / 2, p);
    long long c = (half.a * ((2 * half.b % p + p - half.a) % p)) % p;
    long long d = (half.a * half.a % p + half.b * half.b % p) % p;
    if (n % 2 == 0) {
        fib res = {c, d};
        return res;
    } else {
        fib res = {d, (c + d) % p};
        return res;
    }
}

#define MAX_PERIOD 6000006

int main(){
    long long n, k, p;
    scanf("%lld %lld %lld", &n, &k, &p);
    
    // Allocate memory for cumulative counts
    // Maximum period is 6k, which is up to 6e6 for k=1e6
    // To prevent stack overflow, allocate statically or dynamically
    // Here, we use dynamic allocation
    long long *cum_cnt = (long long*)malloc((6000006) * sizeof(long long));
    if(cum_cnt == NULL){
        return 1;
    }
    
    // Compute Pisano period for F(n) mod k and count s
    long long F0 = 0;
    long long F1 = 1;
    long long j = 1;
    cum_cnt[1] = (F1 == 1) ? 1 : 0;
    long long s = cum_cnt[1];
    
    while(1){
        long long F2 = (F0 + F1) % k;
        F0 = F1;
        F1 = F2;
        j++;
        if(j >= 6000006){
            break; // safety break
        }
        cum_cnt[j] = cum_cnt[j-1] + ((F1 ==1) ? 1 : 0);
        if(F1 ==1){
            s++;
        }
        if(F0 ==0 && F1 ==1){
            j--;
            break;
        }
    }
    
    long long t = j;
    long long total_periods = n / t;
    long long remainder = n % t;
    
    // Compute sum1 = floor(n/t) * s + cum_cnt[remainder]
    // Since n can be up to 1e18 and p up to 1e9, use modulo operations
    long long q = total_periods;
    if(q > 0){
        q = q % p;
    }
    long long sum1_modp = (q * (s % p)) % p;
    if(remainder > t){
        remainder = t;
    }
    if(remainder >=1){
        sum1_modp = (sum1_modp + (cum_cnt[remainder] % p)) % p;
    }
    
    // Compute sum2 = cum_cnt[2]
    long long sum2 = 0;
    if(t >=1){
        sum2 += (cum_cnt[1] >=1) ? 1 : 0;
    }
    if(t >=2){
        sum2 += (cum_cnt[2] - cum_cnt[1] >=1) ? 1 : 0;
    }
    sum2 = sum2 % p;
    
    // D(n) mod p = (sum1 - sum2 + p) % p
    long long D_modp = (sum1_modp - sum2 + p) % p;
    
    // Compute F(n) mod p using fast doubling
    fib Fn = fib_fast_doubling(n, p);
    long long Fmodp = Fn.a;
    
    // a(n) mod p = (F(n) mod p - D(n) mod p + p) % p
    long long anamodp = (Fmodp - D_modp + p) % p;
    
    printf("%lld\n", anamodp);
    
    free(cum_cnt);
    return 0;
}