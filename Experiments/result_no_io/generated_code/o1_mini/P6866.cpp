#include <stdio.h>
#include <string.h>

#define MAX 101

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[MAX][MAX];
    for(int i=0; i<n; i++) {
        scanf("%s", grid[i]);
    }
    int visited[MAX][MAX];
    memset(visited, 0, sizeof(visited));
    int count = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(grid[i][j] == '*' && !visited[i][j]){
                count++;
                // Find the right boundary
                int right = j;
                while(right < m && grid[i][right] == '*') right++;
                // Find the bottom boundary
                int bottom = i;
                while(bottom < n && grid[bottom][j] == '*') bottom++;
                // Mark all cells in the rectangle as visited
                for(int a=i; a<bottom; a++) {
                    for(int b=j; b<right; b++) {
                        visited[a][b] = 1;
                    }
                }
            }
        }
    }
    printf("%d\n", count);
    return 0;
}