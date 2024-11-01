#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

#define MOD 20101009
#define MAX 10000010

int main(){
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll K = n < m ? n : m;
    char *mu = (char*)malloc((K+1) * sizeof(char));
    memset(mu, 1, (K+1) * sizeof(char));
    for(ll p=2; p<=K; p++){
        if(mu[p] != 0){
            for(ll multiple=p; multiple<=K; multiple += p){
                mu[multiple] *= -1;
            }
            for(ll multiple=p*p; multiple<=K; multiple += p*p){
                mu[multiple] = 0;
            }
        }
    }
    ll inv2 = 10050505;
    ll sum = 0;
    for(ll d=1; d<=K; d++){
        if(mu[d] ==0) continue;
        ll t1 = n / d;
        ll t2 = m / d;
        ll t1_sum = t1 % MOD;
        t1_sum = (t1_sum * ((t1 +1) % MOD)) % MOD;
        t1_sum = (t1_sum * inv2) % MOD;
        ll t2_sum = t2 % MOD;
        t2_sum = (t2_sum * ((t2 +1) % MOD)) % MOD;
        t2_sum = (t2_sum * inv2) % MOD;
        ll term = mu[d];
        if(term <0) term += MOD;
        term = (term * d) % MOD;
        term = (term * d) % MOD;
        term = (term * t1_sum) % MOD;
        term = (term * t2_sum) % MOD;
        sum = (sum + term) % MOD;
    }
    printf("%lld\n", sum);
    free(mu);
    return 0;
}