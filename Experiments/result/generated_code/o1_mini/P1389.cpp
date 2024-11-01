#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 150
#define MAX_VAL 1000000000

int main(){
    int N;
    scanf("%d", &N);
    int V[N+1];
    for(int i=1;i<=N;i++) scanf("%d", &V[i]);
    long long A[N+1];
    for(int i=1;i<=N;i++) scanf("%lld", &A[i]);
    
    // dp[i][j] will store the maximum score for subarray i to j
    long long dp[N+2][N+2];
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            dp[i][j] = 0;
        }
    }
    
    // len is the length of the subarray
    for(int len=1; len<=N; len++){
        for(int i=1; i+len-1<=N; i++){
            int j = i + len -1;
            // Check if the segment [i,j] is deletable
            bool deletable = true;
            for(int k=i; k<j; k++){
                if(abs(A[k+1] - A[k]) !=1){
                    deletable = false;
                    break;
                }
            }
            if(deletable){
                for(int k=i+1; k<j; k++){
                    if(A[k] < A[k-1] && A[k] < A[k+1]){
                        deletable = false;
                        break;
                    }
                }
            }
            if(deletable){
                if(V[len] > dp[i][j]){
                    dp[i][j] = V[len];
                }
            }
            // Try all possible partitions
            for(int m=i; m<j; m++){
                if(dp[i][m] + dp[m+1][j] > dp[i][j]){
                    dp[i][j] = dp[i][m] + dp[m+1][j];
                }
            }
        }
    }
    printf("%lld\n", dp[1][N]);
    return 0;
}