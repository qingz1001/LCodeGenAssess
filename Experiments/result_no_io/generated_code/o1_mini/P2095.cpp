#include <stdio.h>
#include <string.h>

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int c[101];
    for(int i=1;i<=k;i++) scanf("%d", &c[i]);
    
    int max_a[101];
    for(int i=1;i<=k;i++) max_a[i] = 0;
    
    for(int i=0;i<n;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        if(a > max_a[b]) max_a[b] = a;
    }
    
    int dp[101] = {0};
    
    for(int j=1; j<=k; j++){
        if(max_a[j] == 0) continue;
        for(int x = m; x >=0; x--){
            for(int t=1; t<=c[j] && x + t <=m; t++){
                if(dp[x + t] < dp[x] + t * max_a[j]){
                    dp[x + t] = dp[x] + t * max_a[j];
                }
            }
        }
    }
    
    int result = 0;
    for(int i=0;i<=m;i++) if(dp[i] > result) result = dp[i];
    printf("%d", result);
    return 0;
}