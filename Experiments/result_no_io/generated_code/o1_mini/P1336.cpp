#include<stdio.h>
#include<limits.h>

typedef long long ll;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int A[m], B[m];
    for(int i=0;i<m;i++) scanf("%d %d", &A[i], &B[i]);
    ll dp[n+1];
    for(int i=0;i<=n;i++) dp[i] = LLONG_MAX;
    dp[0] = 0;
    for(int i=0;i<m;i++){
        int a = A[i], b = B[i];
        ll cost[201];
        for(int x=0;x<=n;x++) {
            if(x ==0) cost[x]=0;
            else{
                ll res=1;
                for(int p=0;p<b;p++) res *=x;
                cost[x] = a * res;
            }
        }
        for(int k=n; k>=0; k--){
            for(int x=1; x<=n -k; x++){
                if(dp[k] != LLONG_MAX && dp[k] + cost[x] < dp[k+x]){
                    dp[k+x] = dp[k] + cost[x];
                }
            }
        }
    }
    printf("%lld", dp[n]);
}