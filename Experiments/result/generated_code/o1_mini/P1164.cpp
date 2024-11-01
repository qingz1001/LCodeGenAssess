#include <stdio.h>
#include <string.h>

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int a[100];
    for(int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    int dp[10001];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for(int i = 0; i < N; i++) {
        for(int j = M; j >= a[i]; j--) {
            dp[j] += dp[j - a[i]];
        }
    }
    printf("%d", dp[M]);
    return 0;
}