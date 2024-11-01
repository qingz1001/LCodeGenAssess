#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DENOM 100
#define MAX_SUM 1000

int N, K;
int bestMax = 0;
int bestSet[15];
int currentSet[15];
int currentSize = 0;

int achievable[MAX_SUM+1];

void updateAchievable(int* denominations, int size) {
    memset(achievable, 0, sizeof(achievable));
    achievable[0] = 1;
    for(int i=0;i<size;i++) {
        for(int j=MAX_SUM; j>=denominations[i]; j--){
            if(achievable[j - denominations[i]]){
                // Count the number of stamps used
                // To limit the number of stamps to N
                // We need another array to track the number of stamps
                // Let's use a temporary array
            }
        }
    }
    // To handle the number of stamps, implement DP with count
    int dp[MAX_SUM+1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 0;
    for(int i=0;i<size;i++) {
        for(int j=MAX_SUM; j>=denominations[i]; j--){
            if(dp[j - denominations[i]] + 1 <= N){
                if(dp[j] == 0 || dp[j] > dp[j - denominations[i]] +1){
                    dp[j] = dp[j - denominations[i]] +1;
                }
            }
        }
    }
    for(int i=1;i<=MAX_SUM;i++) {
        achievable[i] = (dp[i] <= N && dp[i] >0) ? 1 : 0;
    }
}

int getMax(int* denominations, int size){
    updateAchievable(denominations, size);
    int m=0;
    while(achievable[m+1]){
        m++;
    }
    return m;
}

void backtrack(int start, int depth, int* denominations){
    if(depth == K){
        int m = getMax(denominations, K);
        if(m > bestMax){
            bestMax = m;
            for(int i=0;i<K;i++) bestSet[i] = denominations[i];
        }
        return;
    }
    for(int i=start; i<=bestMax+1 && i<=MAX_DENOM; i++){
        // Prune if the next denomination is too large
        if(depth ==0 && i !=1) continue;
        denominations[depth] = i;
        int m = getMax(denominations, depth+1);
        if(m + (K - depth -1)*1 >= bestMax){
            backtrack(i+1, depth+1, denominations);
        }
    }
}

int main(){
    scanf("%d %d", &N, &K);
    int denominations[15];
    backtrack(1, 0, denominations);
    for(int i=0;i<K;i++) printf("%d%c", bestSet[i], (i==K-1)?'\n':' ');
    printf("MAX=%d\n", bestMax);
    return 0;
}