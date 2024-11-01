#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 101
#define MAXK 101
#define INF -9223372036854775807LL

long long a[MAXN][MAXN];
long long dp_prev[MAXN][MAXK];
long long dp_curr[MAXN][MAXK];

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    if(k > n) k = n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            scanf("%lld", &a[i][j]);
        }
    }
    // Initialize dp_prev
    for(int c=0;c<=k;c++) dp_prev[1][c] = INF;
    dp_prev[1][0] = a[1][1];
    if(k >=1) dp_prev[1][1] = 3LL * a[1][1];
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i;j++){
            for(int c=0;c<=k;c++) dp_curr[j][c] = INF;
        }
        for(int j=1;j<=i;j++){
            // From (i-1, j-1)
            if(j-1 >=1){
                for(int c=0;c<=k;c++){
                    if(dp_prev[j-1][c] == INF) continue;
                    // Not triple
                    if(dp_prev[j-1][c] + a[i][j] > dp_curr[j][c]){
                        dp_curr[j][c] = dp_prev[j-1][c] + a[i][j];
                    }
                    // Triple
                    if(c+1 <=k){
                        if(dp_prev[j-1][c] + 3LL * a[i][j] > dp_curr[j][c+1]){
                            dp_curr[j][c+1] = dp_prev[j-1][c] + 3LL * a[i][j];
                        }
                    }
                }
            }
            // From (i-1, j)
            if(j <= i-1){
                for(int c=0;c<=k;c++){
                    if(dp_prev[j][c] == INF) continue;
                    // Not triple
                    if(dp_prev[j][c] + a[i][j] > dp_curr[j][c]){
                        dp_curr[j][c] = dp_prev[j][c] + a[i][j];
                    }
                    // Triple
                    if(c+1 <=k){
                        if(dp_prev[j][c] + 3LL * a[i][j] > dp_curr[j][c+1]){
                            dp_curr[j][c+1] = dp_prev[j][c] + 3LL * a[i][j];
                        }
                    }
                }
            }
        }
        // Copy dp_curr to dp_prev
        for(int j=1;j<=i;j++){
            for(int c=0;c<=k;c++){
                dp_prev[j][c] = dp_curr[j][c];
            }
        }
    }
    long long res = INF;
    for(int j=1;j<=n;j++){
        for(int c=0;c<=k;c++){
            if(dp_prev[j][c] > res){
                res = dp_prev[j][c];
            }
        }
    }
    printf("%lld\n", res);
    return 0;
}