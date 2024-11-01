#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 2001
#define INF 1000000000

int main(){
    char A[MAX], B[MAX];
    int K;
    scanf("%s", A);
    scanf("%s", B);
    scanf("%d", &K);
    int lenA = strlen(A);
    int lenB = strlen(B);
    long long dp[MAX][MAX];
    for(int i=0;i<=lenA;i++){
        for(int j=0;j<=lenB;j++){
            if(i == 0 && j == 0){
                dp[i][j] = 0;
            }
            else if(i == 0){
                dp[i][j] = dp[i][j-1] + K;
            }
            else if(j == 0){
                dp[i][j] = dp[i-1][j] + K;
            }
            else{
                int cost;
                if(A[i-1] != ' ' && B[j-1] != ' '){
                    cost = abs((int)A[i-1] - (int)B[j-1]);
                }
                else if(A[i-1] == ' ' && B[j-1] == ' '){
                    cost = 0;
                }
                else{
                    cost = K;
                }
                long long option1 = dp[i-1][j-1] + cost;
                long long option2 = dp[i-1][j] + K;
                long long option3 = dp[i][j-1] + K;
                if(option1 < option2){
                    if(option1 < option3){
                        dp[i][j] = option1;
                    }
                    else{
                        dp[i][j] = option3;
                    }
                }
                else{
                    if(option2 < option3){
                        dp[i][j] = option2;
                    }
                    else{
                        dp[i][j] = option3;
                    }
                }
            }
        }
    }
    printf("%lld", dp[lenA][lenB]);
    return 0;
}