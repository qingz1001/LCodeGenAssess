#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Function to compute a^b mod m
ll power_mod(ll a, ll b, ll m){
    if(m ==1) return 0;
    ll res =1;
    a = a % m;
    while(b >0){
        if(b &1){
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>=1;
    }
    return res;
}

// Function to compute phi(m)
ll phi(ll m){
    if(m ==0) return 0;
    ll result = m;
    for(ll i=2;i*i<=m;i++){
        if(m%i ==0){
            while(m%i ==0){
                m /=i;
            }
            result -= result /i;
        }
    }
    if(m >1){
        result -= result /m;
    }
    return result;
}

int main(){
    int n;
    scanf("%d", &n);
    ll *a = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &a[i]);
    ll m = 10007;
    ll exponent =1;
    for(int i=n-1;i>=0;i--){
        if(m ==0){
            exponent =0;
            continue;
        }
        ll current_phi = phi(m);
        ll exp_mod = exponent;
        if(m !=1){
            if(exponent >= current_phi){
                exp_mod = exponent % current_phi + current_phi;
            } else {
                exp_mod = exponent;
            }
        }
        exponent = power_mod(a[i], exp_mod, m);
        m = current_phi;
    }
    printf("%lld\n", exponent);
    free(a);
    return 0;
}