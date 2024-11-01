#include <stdio.h>
#include <string.h>

int main(){
    int n, beginLevel, maxLevel;
    scanf("%d %d %d", &n, &beginLevel, &maxLevel);
    int c[n];
    for(int i=0;i<n;i++) scanf("%d", &c[i]);
    
    int dp_prev[maxLevel+1];
    memset(dp_prev, 0, sizeof(dp_prev));
    if(beginLevel >=0 && beginLevel <= maxLevel){
        dp_prev[beginLevel] = 1;
    }
    
    for(int i=0;i<n;i++){
        int dp_curr[maxLevel+1];
        memset(dp_curr, 0, sizeof(dp_curr));
        for(int j=0; j<=maxLevel; j++){
            if(dp_prev[j]){
                if(j + c[i] <= maxLevel){
                    dp_curr[j + c[i]] = 1;
                }
                if(j - c[i] >=0){
                    dp_curr[j - c[i]] = 1;
                }
            }
        }
        memcpy(dp_prev, dp_curr, sizeof(dp_prev));
    }
    
    int result = -1;
    for(int j=maxLevel; j>=0; j--){
        if(dp_prev[j]){
            result = j;
            break;
        }
    }
    printf("%d", result);
    return 0;
}