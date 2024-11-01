#include <stdio.h>

#define MOD 10007

int powmod_func(int a, int b, int mod){
    int res = 1;
    a = a % mod;
    while(b > 0){
        if(b & 1){
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>=1;
    }
    return res;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[m];
    int sum = 0;
    for(int i=0;i<m;i++){
        scanf("%d", &a[i]);
        sum += a[i];
    }
    if(sum != n){
        printf("0\n");
        return 0;
    }
    int fact[n+1];
    fact[0] = 1;
    for(int i=1;i<=n;i++){
        fact[i] = (fact[i-1] * i) % MOD;
    }
    int product = 1;
    for(int i=0;i<m;i++){
        product = (product * fact[a[i]]) % MOD;
    }
    int inv = powmod_func(product, MOD-2, MOD);
    int result = (int)(((long long)fact[n] * inv) % MOD);
    printf("%d\n", result);
    return 0;
}