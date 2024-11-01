#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 1000
#define OFFSET 5000
#define MAX_SUM 10000
#define INF 1001

int main(){
    int n;
    scanf("%d", &n);
    int a, b;
    long long S1 = 0, S2 = 0;
    int c[MAX_N];
    for(int i=0;i<n;i++){
        scanf("%d %d", &a, &b);
        S1 += a;
        S2 += b;
        c[i] = b - a;
    }
    long long D = S1 - S2;
    int dp[MAX_SUM +1];
    for(int i=0;i<=MAX_SUM;i++) dp[i] = INF;
    dp[OFFSET] = 0;
    for(int i=0;i<n;i++){
        int ci = c[i];
        if(ci >=0){
            for(int j=MAX_SUM; j>=0; j--){
                if(j - ci >=0 && dp[j - ci] +1 < dp[j]){
                    dp[j] = dp[j - ci] +1;
                }
            }
        }
        else{
            for(int j=0; j<=MAX_SUM; j++){
                if(j - ci >=0 && j - ci <= MAX_SUM && dp[j - ci] +1 < dp[j]){
                    dp[j] = dp[j - ci] +1;
                }
            }
        }
    }
    long long min_diff = 1e18;
    int best = INF;
    for(int j=0; j<=MAX_SUM; j++){
        if(dp[j] < INF){
            long long current_diff = llabs(D + 2*(j - OFFSET));
            if(current_diff < min_diff){
                min_diff = current_diff;
                best = dp[j];
            }
            else if(current_diff == min_diff && dp[j] < best){
                best = dp[j];
            }
        }
    }
    printf("%d", best);
    return 0;
}