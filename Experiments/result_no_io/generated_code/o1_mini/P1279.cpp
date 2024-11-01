#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 2001
#define INF 1000000000

int main(){
    char A[MAX], B[MAX];
    int K;
    fgets(A, MAX, stdin);
    fgets(B, MAX, stdin);
    
    // Remove possible trailing newline
    int lenA = strlen(A);
    if(A[lenA-1] == '\n') A[lenA-1] = '\0';
    lenA = strlen(A);
    
    int lenB = strlen(B);
    if(B[lenB-1] == '\n') B[lenB-1] = '\0';
    lenB = strlen(B);
    
    scanf("%d", &K);
    
    // Initialize DP table
    long long dp[MAX][MAX];
    dp[0][0] = 0;
    for(int i=1;i<=lenA;i++) dp[i][0] = dp[i-1][0] + K;
    for(int j=1;j<=lenB;j++) dp[0][j] = dp[0][j-1] + K;
    
    for(int i=1;i<=lenA;i++){
        for(int j=1;j<=lenB;j++){
            // Cost of aligning A[i-1] with B[j-1]
            int cost;
            if(A[i-1] != ' ' && B[j-1] != ' ') {
                cost = abs((int)A[i-1] - (int)B[j-1]);
            }
            else if(A[i-1] == ' ' && B[j-1] == ' ') {
                cost = 0;
            }
            else {
                cost = K;
            }
            long long option1 = dp[i-1][j-1] + cost;
            long long option2 = dp[i-1][j] + K;
            long long option3 = dp[i][j-1] + K;
            if(option1 < option2) {
                dp[i][j] = option1 < option3 ? option1 : option3;
            }
            else {
                dp[i][j] = option2 < option3 ? option2 : option3;
            }
        }
    }
    printf("%lld\n", dp[lenA][lenB]);
    return 0;
}