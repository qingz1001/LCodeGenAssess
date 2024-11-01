#include <stdio.h>
#include <string.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[1000][1001];
    for(int i=0; i<n; i++){
        scanf("%s", grid[i]);
    }
    int count = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            // Right
            if(j + 3 < m){
                if(grid[i][j]=='h' && grid[i][j+1]=='e' && grid[i][j+2]=='h' && grid[i][j+3]=='e'){
                    count++;
                }
            }
            // Left
            if(j - 3 >=0){
                if(grid[i][j]=='h' && grid[i][j-1]=='e' && grid[i][j-2]=='h' && grid[i][j-3]=='e'){
                    count++;
                }
            }
            // Down
            if(i + 3 < n){
                if(grid[i][j]=='h' && grid[i+1][j]=='e' && grid[i+2][j]=='h' && grid[i+3][j]=='e'){
                    count++;
                }
            }
            // Up
            if(i - 3 >=0){
                if(grid[i][j]=='h' && grid[i-1][j]=='e' && grid[i-2][j]=='h' && grid[i-3][j]=='e'){
                    count++;
                }
            }
        }
    }
    printf("%d\n", count);
    return 0;
}