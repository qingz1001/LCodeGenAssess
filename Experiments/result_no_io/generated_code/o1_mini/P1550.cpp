#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAXN 301
#define INF 1000000000

int main(){
    int n;
    scanf("%d", &n);
    long long W[MAXN];
    for(int i=1;i<=n;i++) scanf("%lld", &W[i]);
    long long P[MAXN][MAXN];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            scanf("%lld", &P[i][j]);
        }
    }
    int total = n + 1;
    long long key[MAXN];
    bool inMST[MAXN] = {false};
    for(int i=1;i<=total;i++) key[i] = INF;
    key[1] = 0;
    long long res = 0;
    for(int count=1; count<=total; count++){
        int u = -1;
        for(int v=1; v<=total; v++) {
            if(!inMST[v] && (u == -1 || key[v] < key[u])) u = v;
        }
        if(u == -1) break;
        inMST[u] = true;
        res += key[u];
        for(int v=1; v<=n; v++){
            if(u == 1){
                if(key[v+1] > W[v]){
                    key[v+1] = W[v];
                }
            }
            else{
                if(v != u-1 && P[u-1][v] < key[v+1]){
                    key[v+1] = P[u-1][v];
                }
            }
        }
    }
    printf("%lld\n", res);
}