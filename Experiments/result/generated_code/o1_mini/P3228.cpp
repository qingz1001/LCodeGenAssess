#include <stdio.h>
#include <stdint.h>

typedef unsigned long long ull;

// Function to perform modular exponentiation
ull power_mod(ull base, ull exp, ull mod){
    ull result = 1;
    base %= mod;
    while(exp > 0){
        if(exp & 1){
            __int128 temp = (__int128)result * base;
            result = temp % mod;
        }
        __int128 temp = (__int128)base * base;
        base = temp % mod;
        exp >>= 1;
    }
    return result;
}

int main(){
    ull N, K, M, P;
    scanf("%llu %llu %llu %llu", &N, &K, &M, &P);
    
    if(K == 1){
        printf("%llu\n", N % P);
        return 0;
    }
    
    ull a = power_mod(M, K-1, P);
    ull b = ((K-1) % (2*P)) * ((M+1) % (2*P)) % (2*P);
    ull N_mod_2P = N % (2*P);
    ull t;
    if(2*N_mod_2P >= b){
        t = (2*N_mod_2P - b) % (2*P);
    }
    else{
        t = (2*N_mod_2P + 2*P - b) % (2*P);
    }
    ull u = t * a;
    ull ans = (u / 2) % P;
    printf("%llu\n", ans);
}