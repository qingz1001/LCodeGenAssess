#include <stdio.h>

int main(){
    int n, m, c;
    scanf("%d %d %d", &n, &m, &c);
    int p[c];
    for(int i=0;i<c;i++) scanf("%d", &p[i]);
    int grid[n][m];
    int current_color = 1;
    int count = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            grid[i][j] = current_color;
            count++;
            if(count == p[current_color-1]){
                current_color++;
                count = 0;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) printf("%d%c", grid[i][j], j<m-1?' ':'\n');
    }
    return 0;
}