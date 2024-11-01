#include <stdio.h>

int N, M, T;
int grid[5][5];
int FX, FY;
long long count_paths = 0;

int is_valid(int x, int y, int visited){
    if(x < 0 || x >= N || y < 0 || y >= M) return 0;
    if(grid[x][y] || (visited & (1 << (x * M + y)))) return 0;
    return 1;
}

void dfs(int x, int y, int visited){
    if(x == FX && y == FY){
        count_paths++;
        return;
    }
    int dirs[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
    for(int i=0;i<4;i++){
        int nx = x + dirs[i][0];
        int ny = y + dirs[i][1];
        if(is_valid(nx, ny, visited)){
            dfs(nx, ny, visited | (1 << (nx * M + ny)));
        }
    }
}

int main(){
    int SX, SY;
    scanf("%d %d %d", &N, &M, &T);
    scanf("%d %d %d %d", &SX, &SY, &FX, &FY);
    SX--; SY--; FX--; FY--;
    for(int i=0;i<T;i++){
        int ox, oy;
        scanf("%d %d", &ox, &oy);
        grid[ox-1][oy-1] = 1;
    }
    dfs(SX, SY, 1 << (SX * M + SY));
    printf("%lld\n", count_paths);
    return 0;
}