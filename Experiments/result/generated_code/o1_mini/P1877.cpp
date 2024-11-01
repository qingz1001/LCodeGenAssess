#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n, beginLevel, maxLevel;
    scanf("%d %d %d", &n, &beginLevel, &maxLevel);
    int c[n];
    for(int i=0;i<n;i++) scanf("%d", &c[i]);
    int *prev = (int*)calloc(maxLevel+1, sizeof(int));
    int *curr = (int*)calloc(maxLevel+1, sizeof(int));
    if(beginLevel >=0 && beginLevel <= maxLevel){
        prev[beginLevel] = 1;
    }
    for(int i=0;i<n;i++){
        memset(curr, 0, (maxLevel+1)*sizeof(int));
        for(int v=0; v<=maxLevel; v++){
            if(prev[v]){
                if(v + c[i] <= maxLevel) curr[v + c[i]] = 1;
                if(v - c[i] >=0) curr[v - c[i]] = 1;
            }
        }
        // Swap prev and curr
        int *temp = prev;
        prev = curr;
        curr = temp;
    }
    int result = -1;
    for(int v=maxLevel; v>=0; v--){
        if(prev[v]){
            result = v;
            break;
        }
    }
    printf("%d\n", result);
    free(prev);
    free(curr);
    return 0;
}