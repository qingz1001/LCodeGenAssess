#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(){
    int n;
    scanf("%d", &n);
    int W[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &W[i]);
    int P[n+1][n+1];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            scanf("%d", &P[i][j]);
        }
    }
    int inMST[n+1];
    for(int i=1;i<=n;i++) inMST[i]=0;
    int key[n+1];
    for(int i=1;i<=n;i++) key[i]=W[i];
    long long total=0;
    for(int i=0;i<n;i++){
        int min = INT32_MAX;
        int u = -1;
        for(int v=1;v<=n;v++) {
            if(!inMST[v] && key[v]<min){
                min = key[v];
                u = v;
            }
        }
        if(u==-1) break;
        inMST[u]=1;
        total += key[u];
        for(int v=1;v<=n;v++) {
            if(!inMST[v] && P[u][v]<key[v]){
                key[v]=P[u][v];
            }
        }
    }
    printf("%lld\n", total);
}