#include <stdio.h>
#include <stdlib.h>
#define MAX 100001
#define MOD 998244353

long long phi[MAX];
long long S[MAX];

int main(){
    // Initialize phi
    for(int i=0;i<MAX;i++) phi[i] = i;
    for(int p=2;p<MAX;p++){
        if(phi[p] == p){
            for(int j=p; j<MAX; j+=p){
                phi[j] -= phi[j]/p;
            }
        }
    }
    // Compute prefix sums
    S[0] = 0;
    for(int i=1;i<MAX;i++) S[i] = (S[i-1] + phi[i]) % MOD;
    
    int T;
    if(scanf("%d", &T)!=1) return 0;
    while(T--){
        int n, m;
        if(scanf("%d %d", &n, &m)!=2) return 0;
        int D = n < m ? n : m;
        long long sum = 0;
        for(int d=1; d<=D; d++){
            int nd = n / d;
            int md = m / d;
            long long term = ((d * phi[d]) % MOD) * S[nd] % MOD;
            term = term * S[md] % MOD;
            sum = (sum + term) % MOD;
        }
        printf("%lld\n", sum);
    }
    return 0;
}