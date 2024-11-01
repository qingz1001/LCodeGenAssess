#include <stdio.h>
#include <string.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[n][m+1];
    for(int i=0;i<n;i++) {
        scanf("%s", grid[i]);
    }
    int count=0;
    // Check horizontally
    for(int i=0;i<n;i++){
        for(int j=0;j<=m-4;j++){
            if(grid[i][j]=='h' && grid[i][j+1]=='e' && grid[i][j+2]=='h' && grid[i][j+3]=='e'){
                count++;
            }
        }
    }
    // Check vertically
    for(int j=0;j<m;j++){
        for(int i=0;i<=n-4;i++){
            if(grid[i][j]=='h' && grid[i+1][j]=='e' && grid[i+2][j]=='h' && grid[i+3][j]=='e'){
                count++;
            }
        }
    }
    printf("%d", count);
    return 0;
}