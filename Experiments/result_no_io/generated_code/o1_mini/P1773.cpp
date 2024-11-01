#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_L 1001
#define MAX_M 51
#define INF 10000

int main(){
    char s[MAX_L];
    int m;
    scanf("%s", s);
    scanf("%d", &m);
    int L = strlen(s);
    
    // Initialize DP table
    int dp[MAX_L][MAX_M];
    for(int i=0;i<=L;i++) {
        for(int p=0;p<m;p++) {
            dp[i][p] = INF;
        }
    }
    // Initial state: no factors taken yet
    dp[0][0] = 0;
    
    // Iterate through each position
    for(int i=0;i<L;i++){
        for(int p=0;p<m;p++){
            if(dp[i][p] < INF){
                int num_mod = 0;
                for(int j=i; j<L; j++){
                    num_mod = (num_mod *10 + (s[j]-'0')) % m;
                    int new_p, new_k;
                    if(i ==0 && p ==0){
                        new_p = num_mod;
                        new_k = 0;
                    }
                    else{
                        new_p = (p * num_mod) % m;
                        new_k = dp[i][p] +1;
                    }
                    if(new_k < dp[j+1][new_p]){
                        dp[j+1][new_p] = new_k;
                    }
                }
            }
        }
    }
    
    // Find min_x and min_k
    int min_x = -1, min_k = INF;
    for(int p=0;p<m;p++){
        if(dp[L][p] < INF){
            if(min_x == -1 || p < min_x || (p == min_x && dp[L][p] < min_k)){
                min_x = p;
                min_k = dp[L][p];
            }
        }
    }
    
    // Find max_x and its min_k
    int max_x = -1, max_k = INF;
    for(int p=0;p<m;p++){
        if(dp[L][p] < INF){
            if(max_x == -1 || p > max_x || (p == max_x && dp[L][p] < max_k)){
                max_x = p;
                max_k = dp[L][p];
            }
        }
    }
    
    printf("%d %d %d %d\n", min_x, min_k, max_x, max_k);
    return 0;
}