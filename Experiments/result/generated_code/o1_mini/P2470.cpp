#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 51

int min(int a, int b) {
    return a < b ? a : b;
}

int main(){
    char s[MAX];
    scanf("%s", s);
    int n = strlen(s);
    int dp[MAX][MAX];
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            dp[i][j] = INT32_MAX;
        }
    }
    // buffer_start = -1 mapped to n
    dp[0][n] = 0;
    for(int pos=0; pos<=n; pos++) {
        for(int buf=0; buf<=n; buf++) {
            if(dp[pos][buf] == INT32_MAX) continue;
            // Case 1: Output next character
            if(pos < n){
                if(dp[pos+1][buf] > dp[pos][buf] + 1){
                    dp[pos+1][buf] = dp[pos][buf] +1;
                }
            }
            // Case 2: Start 'M' with buffer
            for(int l=1; l <= n - pos; l++){
                int t =1;
                while(pos + l*t <=n){
                    int match =1;
                    for(int k=0; k<l; k++){
                        if(s[pos + k] != s[pos + l*t + k - l*t]){
                            match =0;
                            break;
                        }
                    }
                    // Check if all t repeats match
                    for(int ti=1; ti<t; ti++){
                        for(int k=0; k<l; k++){
                            if(s[pos + k] != s[pos + ti*l + k]){
                                match =0;
                                break;
                            }
                        }
                        if(!match) break;
                    }
                    if(match){
                        t++;
                    }
                    else{
                        break;
                    }
                }
                t--;
                for(int repeat=1; repeat<=t; repeat++){
                    int new_pos = pos + l*repeat;
                    int new_buf = pos;
                    int compressed_len = 1 + l + (repeat-1);
                    if(dp[new_pos][new_buf] > dp[pos][buf] + compressed_len){
                        dp[new_pos][new_buf] = dp[pos][buf] + compressed_len;
                    }
                }
            }
            // Case 3: Output 'R'
            if(pos < n){
                int buffer_length = (buf == n) ? pos : pos - buf;
                if(buffer_length >0 && pos + buffer_length <=n){
                    int match =1;
                    for(int k=0; k<buffer_length; k++){
                        if(s[k + (buf == n ? 0 : buf)] != s[pos + k]){
                            match =0;
                            break;
                        }
                    }
                    if(match){
                        int new_pos = pos + buffer_length;
                        if(dp[new_pos][buf] > dp[pos][buf] +1){
                            dp[new_pos][buf] = dp[pos][buf] +1;
                        }
                    }
                }
            }
        }
    }
    int answer = INT32_MAX;
    for(int buf=0; buf<=n; buf++){
        if(dp[n][buf] < answer){
            answer = dp[n][buf];
        }
    }
    printf("%d\n", answer);
}