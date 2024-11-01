#include <stdio.h>
#include <string.h>

#define INF 1000000

int min(int a, int b){
    return a < b ? a : b;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Case 1: First room not occupied
    int dp1[m+1][n+1][2];
    for(int i=0;i<=m;i++) {
        for(int j=0;j<=n;j++) {
            dp1[i][j][0] = dp1[i][j][1] = INF;
        }
    }
    dp1[0][0][0] = 0;
    
    for(int i=0;i<m;i++){
        for(int j=0;j<=n;j++){
            for(int p=0;p<=1;p++){
                if(dp1[i][j][p] == INF) continue;
                // Do not occupy
                if(dp1[i+1][j][0] > dp1[i][j][p]){
                    dp1[i+1][j][0] = dp1[i][j][p];
                }
                // Occupy
                if(j < n){
                    int anger = p ==1 ? 1 : 0;
                    if(dp1[i+1][j+1][1] > dp1[i][j][p] + anger){
                        dp1[i+1][j+1][1] = dp1[i][j][p] + anger;
                    }
                }
            }
        }
    }
    
    int res1 = INF;
    for(int p=0;p<=1;p++){
        if(p ==1){
            // First room not occupied, last occupied but first not, no extra anger
            res1 = min(res1, dp1[m][n][p]);
        }
        else{
            res1 = min(res1, dp1[m][n][p]);
        }
    }
    
    // Case 2: First room occupied
    int dp2[m+1][n+1][2];
    for(int i=0;i<=m;i++) {
        for(int j=0;j<=n;j++) {
            dp2[i][j][0] = dp2[i][j][1] = INF;
        }
    }
    if(n >=1){
        dp2[1][1][1] = 0;
    }
    
    for(int i=1;i<m;i++){
        for(int j=0;j<=n;j++){
            for(int p=0;p<=1;p++){
                if(dp2[i][j][p] == INF) continue;
                // Do not occupy
                if(dp2[i+1][j][0] > dp2[i][j][p]){
                    dp2[i+1][j][0] = dp2[i][j][p];
                }
                // Occupy
                if(j < n){
                    int anger = p ==1 ? 1 : 0;
                    if(dp2[i+1][j+1][1] > dp2[i][j][p] + anger){
                        dp2[i+1][j+1][1] = dp2[i][j][p] + anger;
                    }
                }
            }
        }
    }
    
    int res2 = INF;
    for(int p=0;p<=1;p++){
        if(p ==1){
            // First room occupied, last room occupied, add 1
            if(n >=1){
                if(dp2[m][n][p] +1 < res2){
                    res2 = dp2[m][n][p] +1;
                }
            }
        }
        else{
            // First room occupied, last room not occupied
            res2 = min(res2, dp2[m][n][p]);
        }
    }
    
    int final_res = INF;
    if(n <= m){
        if(res1 < final_res){
            final_res = res1;
        }
        if(res2 < final_res){
            final_res = res2;
        }
    }
    
    printf("%d\n", final_res);
}