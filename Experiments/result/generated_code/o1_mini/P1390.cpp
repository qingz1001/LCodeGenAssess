#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    ll* phi = (ll*)malloc((n+1) * sizeof(ll));
    for(int i=0;i<=n;i++) phi[i] = i;
    for(int p=2;p<=n;p++){
        if(phi[p] == p){
            for(int multiple=p; multiple<=n; multiple += p){
                phi[multiple] -= phi[multiple] / p;
            }
        }
    }
    ll sum = 0;
    for(int d=1; d<=n; d++){
        ll k = n / d;
        if(k >=2){
            sum += phi[d] * (k * (k -1) /2);
        }
    }
    printf("%lld\n", sum);
    free(phi);
    return 0;
}