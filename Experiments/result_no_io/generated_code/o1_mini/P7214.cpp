#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long ll;

typedef struct {
    ll Ti;
    ll Li;
    ll Ri;
    ll Ci;
} Scheme;

int cmp(const void *a, const void *b){
    Scheme *sa = (Scheme*)a;
    Scheme *sb = (Scheme*)b;
    if(sa->Ri != sb->Ri) return sa->Ri < sb->Ri ? -1 : 1;
    return 0;
}

#define INF 1000000000000000000LL

int main(){
    ll N, M;
    scanf("%lld %lld", &N, &M);
    Scheme *schemes = (Scheme*)malloc(sizeof(Scheme)*M);
    for(ll i=0;i<M;i++) {
        scanf("%lld %lld %lld %lld", &schemes[i].Ti, &schemes[i].Li, &schemes[i].Ri, &schemes[i].Ci);
    }
    qsort(schemes, M, sizeof(Scheme), cmp);
    ll *dp = (ll*)malloc(sizeof(ll)*(N+1));
    for(ll i=0;i<=N;i++) dp[i] = INF;
    dp[0] = 0;
    ll j = 0;
    for(ll i=1;i<=N;i++){
        while(j < M && schemes[j].Ri == i){
            if(schemes[j].Li-1 >=0 && dp[schemes[j].Li-1] + schemes[j].Ci < dp[i]){
                dp[i] = dp[schemes[j].Li-1] + schemes[j].Ci;
            }
            j++;
        }
        if(dp[i-1] < dp[i]){
            dp[i] = dp[i-1];
        }
    }
    if(dp[N] >= INF) printf("-1\n");
    else printf("%lld\n", dp[N]);
    free(schemes);
    free(dp);
    return 0;
}