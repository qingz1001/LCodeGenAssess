#include <stdio.h>
#include <stdlib.h>

#define MAX 100005
#define MOD 998244353

typedef long long ll;

ll phi[MAX];
ll sum_phi[MAX];

int main(){
    // Initialize phi
    for(int i=0;i<MAX;i++) phi[i]=i;
    for(int p=2;p<MAX;p++){
        if(phi[p]==p){
            for(int k=p; k<MAX; k+=p){
                phi[k] -= phi[k]/p;
            }
        }
    }
    // Compute prefix sum of phi
    for(int i=1;i<MAX;i++) sum_phi[i] = sum_phi[i-1] + phi[i];
    
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m;
        scanf("%d %d", &n, &m);
        int limit = n < m ? n : m;
        ll res =0;
        for(int k=1;k<=limit;k++){
            ll cnt_n = n /k;
            ll cnt_m = m /k;
            res = (res + (phi[k] * cnt_n % MOD) * cnt_m % MOD) % MOD;
        }
        printf("%lld\n", res);
    }
    return 0;
}