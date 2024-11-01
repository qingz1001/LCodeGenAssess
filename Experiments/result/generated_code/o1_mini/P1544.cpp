#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    if(k > n) k = n;
    ll a[101][101];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=i;j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    // Initialize DP
    ll dp_prev[101][101];
    for(int j=0; j<=k; j++) {
        dp_prev[j][0] = 0;
    }
    // Initialize first row
    ll dp_curr[101][101];
    memset(dp_prev, 0x80, sizeof(dp_prev));
    // Set first position
    for(int c=0; c<=k; c++) {
        dp_prev[1][c] = (c >=1) ? a[1][1]*3 : a[1][1];
    }
    // Iterate through rows
    for(int i=2;i<=n;i++) {
        memset(dp_curr, 0x80, sizeof(dp_curr));
        for(int j=1; j<=i; j++) {
            for(int c=0; c<=k; c++) {
                // From left
                if(j-1 >=1){
                    // Not triple
                    if(dp_prev[j-1][c] + a[i][j] > dp_curr[j][c]){
                        dp_curr[j][c] = dp_prev[j-1][c] + a[i][j];
                    }
                    // Triple
                    if(c >0 && dp_prev[j-1][c-1] + a[i][j]*3 > dp_curr[j][c]){
                        dp_curr[j][c] = dp_prev[j-1][c-1] + a[i][j]*3;
                    }
                }
                // From right
                if(j <= i-1){
                    // Not triple
                    if(dp_prev[j][c] + a[i][j] > dp_curr[j][c]){
                        dp_curr[j][c] = dp_prev[j][c] + a[i][j];
                    }
                    // Triple
                    if(c >0 && dp_prev[j][c-1] + a[i][j]*3 > dp_curr[j][c]){
                        dp_curr[j][c] = dp_prev[j][c-1] + a[i][j]*3;
                    }
                }
            }
        }
        // Copy current to prev
        for(int j=1; j<=i; j++) {
            for(int c=0; c<=k; c++) {
                dp_prev[j][c] = dp_curr[j][c];
            }
        }
    }
    // Find the maximum
    ll res = -__INT64_MAX__;
    for(int j=1; j<=n; j++) {
        for(int c=0; c<=k; c++) {
            if(dp_prev[j][c] > res){
                res = dp_prev[j][c];
            }
        }
    }
    printf("%lld", res);
}