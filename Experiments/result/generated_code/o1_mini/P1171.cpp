#include <stdio.h>
#include <string.h>

#define INF 1000000000
#define MAXN 20
#define MAXMASK (1<<20)

int n;
int s[20][20];
int dp_array[1<<20][20];

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) {
            scanf("%d", &s[i][j]);
        }
    }
    memset(dp_array, 0x3f, sizeof(dp_array));
    dp_array[1<<0][0] = 0;
    for(int mask=0; mask<(1<<n); mask++){
        for(int u=0; u<n; u++){
            if (mask & (1<<u)){
                for(int v=0; v<n; v++){
                    if(!(mask & (1<<v))){
                        int new_mask = mask | (1<<v);
                        if(dp_array[new_mask][v] > dp_array[mask][u] + s[u][v]){
                            dp_array[new_mask][v] = dp_array[mask][u] + s[u][v];
                        }
                    }
                }
            }
        }
    }
    int full_mask = (1<<n) -1;
    int res = INF;
    for(int u=0; u<n; u++){
        if(u ==0) continue;
        if(dp_array[full_mask][u] + s[u][0] < res){
            res = dp_array[full_mask][u] + s[u][0];
        }
    }
    printf("%d", res);
    return 0;
}