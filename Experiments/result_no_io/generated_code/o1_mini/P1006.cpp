#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define INF -1000000000

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int grid[MAX+1][MAX+1];
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=n;j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    int k_max = m + n -2;
    // Initialize DP arrays
    int prevDP[MAX+1][MAX+1];
    int currDP[MAX+1][MAX+1];
    for(int i=0;i<=m;i++) {
        for(int j=0;j<=m;j++) {
            prevDP[i][j] = INF;
        }
    }
    // Initialize step 0
    prevDP[1][1] = grid[1][1];
    for(int k=1; k<=k_max; k++) {
        // Initialize current DP to INF
        for(int i=0;i<=m;i++) {
            for(int j=0;j<=m;j++) {
                currDP[i][j] = INF;
            }
        }
        for(int i1=1; i1<=m; i1++) {
            int j1 = k + 2 - i1;
            if(j1 <1 || j1 >n) continue;
            for(int i2=1; i2<=m; i2++) {
                int j2 = k + 2 - i2;
                if(j2 <1 || j2 >n) continue;
                if(i1 == i2 && j1 == j2){
                    if(!((i1 ==1 && j1 ==1) || (i1 ==m && j1 ==n))) continue;
                }
                int value = grid[i1][j1];
                if(!(i1 ==i2 && j1 ==j2)){
                    value += grid[i2][j2];
                }
                int max_prev = INF;
                // from (i1-1, i2-1)
                if(i1 >1 && i2 >1 && prevDP[i1-1][i2-1] > max_prev){
                    max_prev = prevDP[i1-1][i2-1];
                }
                // from (i1-1, i2)
                if(i1 >1 && j2 >1 && prevDP[i1-1][i2] > max_prev){
                    max_prev = prevDP[i1-1][i2];
                }
                // from (i1, i2-1)
                if(j1 >1 && i2 >1 && prevDP[i1][i2-1] > max_prev){
                    max_prev = prevDP[i1][i2-1];
                }
                // from (i1, i2)
                if(j1 >1 && j2 >1 && prevDP[i1][i2] > max_prev){
                    max_prev = prevDP[i1][i2];
                }
                if(max_prev != INF){
                    if(currDP[i1][i2] < max_prev + value){
                        currDP[i1][i2] = max_prev + value;
                    }
                }
            }
        }
        // Swap DP arrays
        for(int i=0;i<=m;i++) {
            for(int j=0;j<=m;j++) {
                prevDP[i][j] = currDP[i][j];
            }
        }
    }
    int result = prevDP[m][m];
    printf("%d\n", result);
}