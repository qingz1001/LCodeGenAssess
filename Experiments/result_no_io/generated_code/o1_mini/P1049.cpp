#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int V, n;
    scanf("%d", &V);
    scanf("%d", &n);
    int *volumes = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &volumes[i]);
    // Initialize DP
    char *dp = (char*)calloc(V+1, sizeof(char));
    dp[0] = 1;
    for(int i=0;i<n;i++){
        int vol = volumes[i];
        for(int j=V; j>=vol; j--){
            if(dp[j - vol]) dp[j] = 1;
        }
    }
    // Find the maximum j <= V with dp[j]=1
    int max = 0;
    for(int j=V; j>=0; j--){
        if(dp[j]){
            max = j;
            break;
        }
    }
    printf("%d\n", V - max);
    free(volumes);
    free(dp);
    return 0;
}