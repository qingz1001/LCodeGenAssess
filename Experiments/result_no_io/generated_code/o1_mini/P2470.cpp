#include <stdio.h>
#include <string.h>
#include <limits.h>

#define INF 1000

int min(int a, int b) {
    return a < b ? a : b;
}

int main(){
    char s[55];
    scanf("%s", s);
    int n = strlen(s);
    // dp[i][m_shift] = min compressed length for first i chars with m = m_shift -1
    int dp[51][51];
    for(int i=0;i<=n;i++) {
        for(int m=0;m<=n;m++) {
            dp[i][m] = INF;
        }
    }
    dp[0][0] =0;
    for(int i=0;i<=n;i++) {
        for(int m_shift=0;m_shift<=n;m_shift++) {
            if(dp[i][m_shift] == INF) continue;
            // Option1: output s[i] as itself
            if(i < n){
                if(dp[i+1][m_shift] > dp[i][m_shift] +1){
                    dp[i+1][m_shift] = dp[i][m_shift] +1;
                }
            }
            // Option2: insert 'M' and mark buffer starting at i
            if(i < n){
                for(int l=1;l<=n-i;l++){
                    if(i + l > n) break;
                    if(dp[i + l][i +1] > dp[i][m_shift] +1 + l){
                        dp[i + l][i +1] = dp[i][m_shift] +1 + l;
                    }
                }
            }
            // Option3: insert 'R'
            int buffer_start;
            if(m_shift ==0){
                buffer_start =0;
            }
            else{
                buffer_start = m_shift -1;
            }
            int buffer_length = i - buffer_start;
            if(buffer_length >0 && i + buffer_length <=n){
                int match =1;
                for(int k=0;k<buffer_length;k++){
                    if(s[buffer_start +k] != s[i +k]){
                        match =0;
                        break;
                    }
                }
                if(match){
                    if(dp[i + buffer_length][m_shift] > dp[i][m_shift] +1){
                        dp[i + buffer_length][m_shift] = dp[i][m_shift] +1;
                    }
                }
            }
        }
    }
    int result = INF;
    for(int m=0;m<=n;m++) {
        if(dp[n][m] < result){
            result = dp[n][m];
        }
    }
    printf("%d\n", result);
    return 0;
}