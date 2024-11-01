#include <stdio.h>
#include <string.h>

int main(){
    int V, n;
    scanf("%d", &V);
    scanf("%d", &n);
    int items[n];
    for(int i=0;i<n;i++) scanf("%d", &items[i]);
    char dp[V+1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for(int i=0;i<n;i++){
        for(int j=V; j>=items[i]; j--){
            if(dp[j - items[i]]) dp[j] = 1;
        }
    }
    for(int j=V; j>=0; j--){
        if(dp[j]){
            printf("%d\n", V - j);
            break;
        }
    }
    return 0;
}