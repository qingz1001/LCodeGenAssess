#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    char grid[n][n+1];
    for(int i=0;i<n;i++) {
        scanf("%s", grid[i]);
    }
    // Initialize height array
    int height[n][n];
    for(int j=0;j<n;j++) {
        height[0][j] = (grid[0][j] == 'W') ? 1 : 0;
    }
    for(int i=1;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(grid[i][j] == 'W') height[i][j] = height[i-1][j] +1;
            else height[i][j] = 0;
        }
    }
    long long total =0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(height[i][j]==0) continue;
            int min_h = height[i][j];
            for(int k=j; k>=0; k--){
                if(height[i][k]==0) break;
                if(height[i][k] < min_h) min_h = height[i][k];
                total += min_h;
            }
        }
    }
    printf("%lld", total);
    return 0;
}