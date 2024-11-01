#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    // Initialize phi
    ll *phi = (ll*)malloc((n+1) * sizeof(ll));
    for(int i=0;i<=n;i++) phi[i] = i;
    // Sieve to compute phi
    for(int i=2;i<=n;i++){
        if(phi[i] == i){
            for(int j=i; j<=n; j+=i){
                phi[j] -= phi[j] / i;
            }
        }
    }
    // Calculate the sum
    ll sum = 0;
    for(int d=1; d<=n; d++){
        ll cnt = n/d;
        if(cnt < 2) continue;
        sum += phi[d] * cnt * (cnt -1) / 2;
    }
    printf("%lld\n", sum);
    free(phi);
    return 0;
}