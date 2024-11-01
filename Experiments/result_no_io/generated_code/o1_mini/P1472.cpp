#include <stdio.h>
#include <string.h>

#define MOD 9901

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    // dp[k][n] represents number of trees with n nodes and depth at most k
    int dp[101][201];
    memset(dp, 0, sizeof(dp));
    // Initialize dp[0][n] =0
    for(int cur_k=1; cur_k<=k; cur_k++){
        for(int cur_n=1; cur_n<=200; cur_n+=2){
            if(cur_n ==1){
                dp[cur_k][cur_n] =1;
                continue;
            }
            if(cur_k ==1){
                dp[cur_k][cur_n] =0;
                continue;
            }
            int sum =0;
            for(int left=1; left<=cur_n-2; left+=2){
                int right = cur_n -1 -left;
                if(left < right){
                    sum += (dp[cur_k-1][left] * dp[cur_k-1][right]) % MOD;
                    if(sum >= MOD) sum -= MOD;
                }
                else if(left == right){
                    long long temp = ((long long)dp[cur_k-1][left] * dp[cur_k-1][right] + dp[cur_k-1][left]) % MOD;
                    temp = (temp * 4951) % MOD; // 4951 is inverse of 2 mod 9901
                    sum += temp;
                    if(sum >= MOD) sum -= MOD;
                }
            }
            dp[cur_k][cur_n] = sum;
        }
    }
    int dp_k = (k >=1 && k <=100) ? dp[k][n] :0;
    int dp_km1 = (k-1 >=1 && k-1 <=100) ? dp[k-1][n] :0;
    int answer = (dp_k - dp_km1 + MOD) % MOD;
    printf("%d\n", answer);
    return 0;
}