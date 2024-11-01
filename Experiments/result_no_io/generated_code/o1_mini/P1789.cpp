#include <stdio.h>

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    int grid[100][100] = {0};
    // Define torch offsets
    int torch_dx[13] = {-2,-1,-1,-1,0,0,0,0,0,+1,+1,+1,+2};
    int torch_dy[13] = {0,-1,0,+1,-2,-1,0,+1,+2,-1,0,+1,0};
    // Read torches
    for(int i=0;i<m;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        grid[x][y] = 1; // object
        for(int j=0;j<13;j++){
            int nx = x + torch_dx[j];
            int ny = y + torch_dy[j];
            if(nx >=0 && nx <n && ny >=0 && ny <n){
                grid[nx][ny] = 1;
            }
        }
    }
    // Read beacons
    for(int i=0;i<k;i++){
        int o, p;
        scanf("%d %d", &o, &p);
        o--; p--;
        grid[o][p] = 1; // object
        for(int dx=-2; dx<=2; dx++){
            for(int dy=-2; dy<=2; dy++){
                int nx = o + dx;
                int ny = p + dy;
                if(nx >=0 && nx <n && ny >=0 && ny <n){
                    grid[nx][ny] = 1;
                }
            }
        }
    }
    // Count monsters
    int count=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]==0){
                count++;
            }
        }
    }
    printf("%d", count);
    return 0;
}