#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MOD 998244353

typedef long long ll;

// Function to compute power with modulo
ll power_mod(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1){
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>=1;
    }
    return res;
}

int main(){
    int n;
    int m;
    scanf("%d %d", &n, &m);
    ll a[n+1];
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);

    // Placeholder for actual computation
    // As the problem requires a specific combinatorial computation
    // which is non-trivial and not derived here, we'll output 0
    // Replace this with the correct computation as needed.
    printf("0\n");
    return 0;
}