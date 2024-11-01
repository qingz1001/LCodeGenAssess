#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

ll power_mod(ll base, ll exp, ll mod){
    ll res = 1;
    base %= mod;
    while(exp > 0){
        if(exp & 1){
            res = res * base % mod;
        }
        base = base * base % mod;
        exp >>=1;
    }
    return res;
}

int main(){
    ll n, p;
    scanf("%lld %lld", &n, &p);
    // Compute Möbius function
    ll N = n;
    int *mu = (int*)malloc((N+1) * sizeof(int));
    for(int i=0;i<=N;i++) mu[i]=1;
    int *is_prime = (int*)malloc((N+1) * sizeof(int));
    for(int i=0;i<=N;i++) is_prime[i]=1;
    is_prime[0]=is_prime[1]=0;
    for(int i=2;i<=N;i++){
        if(is_prime[i]){
            for(int j=i; j<=N; j+=i){
                is_prime[j]=0;
                mu[j] *= -1;
            }
            ll sq = (ll)i * i;
            for(ll j=sq; j<=N; j+=sq){
                mu[j] = 0;
            }
        }
    }
    ll total =0;
    for(ll d=1; d<=N; d++){
        if(mu[d]==0) continue;
        ll cnt = (n-1)/d;
        ll term = power_mod(3, cnt, p);
        if(mu[d]==1){
            total = (total + term) % p;
        }
        else{
            total = (total - term) % p;
            if(total <0) total += p;
        }
    }
    printf("%lld\n", total);
    free(mu);
    free(is_prime);
    return 0;
}