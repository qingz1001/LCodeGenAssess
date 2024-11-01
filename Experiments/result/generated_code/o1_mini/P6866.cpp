#include <stdio.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[100][101];
    for(int i=0; i<n; i++){
        scanf("%s", grid[i]);
    }
    int visited[100][100] = {0};
    int count = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j] == '*' && !visited[i][j]){
                // Find the width of the rectangle
                int l = j;
                while(l < m && grid[i][l] == '*'){
                    l++;
                }
                int width = l - j;
                // Find the height of the rectangle
                int k = i;
                while(k < n){
                    int valid = 1;
                    for(int c = j; c < j + width; c++){
                        if(grid[k][c] != '*'){
                            valid = 0;
                            break;
                        }
                    }
                    if(valid){
                        k++;
                    }
                    else{
                        break;
                    }
                }
                int height = k - i;
                // Mark all cells of the rectangle as visited
                for(int x = i; x < i + height; x++){
                    for(int y = j; y < j + width; y++){
                        visited[x][y] = 1;
                    }
                }
                count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}