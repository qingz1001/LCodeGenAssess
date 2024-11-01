#include <stdio.h>
#include <string.h>

#define MAX_M 51
#define MAX_N 51
#define MAX_K 101
#define INF -1000000000

int max(int a, int b) {
    return a > b ? a : b;
}

int grid[MAX_M][MAX_N];
int dp_prev[MAX_M][MAX_M];
int dp_curr[MAX_M][MAX_M];

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=n;j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    // Initialize DP
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=m;j++) {
            dp_prev[i][j] = INF;
        }
    }
    dp_prev[1][1] = grid[1][1];
    // Iterate over steps
    for(int k=1; k <= m+n-2; k++){
        // Reset current DP
        for(int i=1;i<=m;i++) {
            for(int j=1;j<=m;j++) {
                dp_curr[i][j] = INF;
            }
        }
        // Iterate over possible positions
        for(int i1=1; i1<=m; i1++) {
            int j1 = k+2 - i1;
            if(j1 <1 || j1 >n) continue;
            for(int i2=1; i2<=m; i2++) {
                int j2 = k+2 - i2;
                if(j2 <1 || j2 >n) continue;
                // Calculate value
                int val;
                if(i1 == i2 && j1 == j2){
                    if( (i1 ==1 && j1 ==1) || (i1 ==m && j1 ==n) ){
                        val = grid[i1][j1];
                    }
                    else{
                        continue;
                    }
                }
                else{
                    val = grid[i1][j1] + grid[i2][j2];
                }
                // Iterate over previous moves
                for(int pi1 = i1-1; pi1 <= i1; pi1++) {
                    for(int pi2 = i2-1; pi2 <= i2; pi2++) {
                        if(pi1 <1 || pi2 <1) continue;
                        int pj1 = k+1 +2 - pi1;
                        int pj2 = k+1 +2 - pi2;
                        if(pj1 <1 || pj1 >n || pj2 <1 || pj2 >n) continue;
                        if(dp_prev[pi1][pi2] == INF) continue;
                        int temp = dp_prev[pi1][pi2] + val;
                        if(temp > dp_curr[i1][i2]){
                            dp_curr[i1][i2] = temp;
                        }
                    }
                }
            }
        }
        // Swap DP
        for(int i=1;i<=m;i++) {
            for(int j=1;j<=m;j++) {
                dp_prev[i][j] = dp_curr[i][j];
            }
        }
    }
    int result = dp_prev[m][m];
    printf("%d\n", result);
    return 0;
}