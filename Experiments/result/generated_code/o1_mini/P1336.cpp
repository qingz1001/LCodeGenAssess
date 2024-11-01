#include <stdio.h>
#include <stdint.h>

#define MAX_M 20
#define MAX_N 200
#define INF 1000000000000000000LL

typedef long long ll;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    ll A[MAX_M];
    int B[MAX_M];
    for(int i=0;i<m;i++) {
        scanf("%lld %d", &A[i], &B[i]);
    }
    // Precompute power[i][k] = k^B[i]
    ll power_val[MAX_M][MAX_N+1];
    for(int i=0;i<m;i++){
        for(int k=0;k<=n;k++){
            if(k ==0){
                power_val[i][k]=0;
            }
            else{
                ll temp =1;
                for(int p=0;p<B[i];p++) temp *=k;
                power_val[i][k]=temp;
            }
        }
    }
    // Initialize DP
    ll dp[MAX_N+1];
    for(int j=0;j<=n;j++) dp[j]=INF;
    dp[0]=0;
    // DP process
    for(int i=0;i<m;i++){
        for(int j=n; j>=0; j--){
            if(dp[j] < INF){
                for(int k=1; k<=n-j; k++){
                    ll cost = dp[j] + A[i] * power_val[i][k];
                    if(cost < dp[j+k]){
                        dp[j+k] = cost;
                    }
                }
            }
        }
    }
    printf("%lld\n", dp[n]);
    return 0;
}