#include <stdio.h>
#include <string.h>

#define MAX 200
#define INF -2147483647

int main(){
    int N;
    scanf("%d", &N);
    int head_orig[100];
    for(int i=0;i<N;i++) scanf("%d", &head_orig[i]);
    int head[200];
    for(int i=0;i<2*N;i++) head[i] = head_orig[i%N];
    long long dp[200][200];
    for(int i=0;i<2*N;i++) {
        for(int j=0;j<2*N;j++) {
            dp[i][j] = 0;
        }
    }
    for(int length=2; length<=N; length++){
        for(int i=0; i+length-1 < 2*N; i++){
            int j = i + length -1;
            dp[i][j] = INF;
            for(int k=i; k<j; k++){
                long long temp = dp[i][k] + dp[k+1][j] + (long long)head[i] * head[k+1] * head[j+1];
                if(temp > dp[i][j]) dp[i][j] = temp;
            }
        }
    }
    long long maxE = 0;
    for(int i=0;i<N;i++){
        if(dp[i][i+N-1] > maxE) maxE = dp[i][i+N-1];
    }
    printf("%lld", maxE);
    return 0;
}