#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

int main(){
    int N, L;
    scanf("%d %d", &N, &L);
    int A, B;
    scanf("%d %d", &A, &B);
    // Read cow intervals but not used in DP
    for(int i=0;i<N;i++){
        int S, E;
        scanf("%d %d", &S, &E);
    }
    // Allocate dp array
    int* dp = (int*)malloc((L+1)*sizeof(int));
    for(int i=0;i<=L;i++) dp[i] = INF;
    dp[0] = 0;
    for(int i=1;i<=L;i++){
        for(int x=A; x<=B; x++){
            int j = i - 2*x;
            if(j < 0) continue;
            if( (j + i) % 2 != 0 ) continue;
            if(dp[j] + 1 < dp[i]){
                dp[i] = dp[j] +1;
            }
        }
    }
    if(dp[L] >= INF){
        printf("-1\n");
    }
    else{
        printf("%d\n", dp[L]);
    }
    free(dp);
    return 0;
}