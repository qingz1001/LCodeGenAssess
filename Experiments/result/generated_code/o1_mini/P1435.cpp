#include <stdio.h>
#include <string.h>

#define MAX 1001

int min(int a, int b) {
    return a < b ? a : b;
}

int main(){
    char s[MAX];
    if (!fgets(s, MAX, stdin)) return 0;
    int n = strlen(s);
    if(s[n-1]=='\n') { s[n-1] = '\0'; n--;}
    int dp[MAX][MAX];
    for(int i=0;i<n;i++) dp[i][i]=0;
    for(int len=2; len<=n; len++){
        for(int i=0;i<=n-len;i++){
            int j = i + len -1;
            if(s[i]==s[j]){
                dp[i][j] = dp[i+1][j-1];
            }
            else{
                dp[i][j] = min(dp[i+1][j], dp[i][j-1]) +1;
            }
        }
    }
    printf("%d\n", dp[0][n-1]);
    return 0;
}