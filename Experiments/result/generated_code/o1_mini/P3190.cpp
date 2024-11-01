#include <stdio.h>
#include <string.h>
#include <limits.h>

int n, m;
int grid[100][6];
long long max_sum = LLONG_MIN;
unsigned char visited_cells[100];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void dfs(int start_r, int start_c, int current_r, int current_c, long long current_sum, int path_len){
    for(int dir = 0; dir < 4; dir++){
        int nr = current_r + dr[dir];
        int nc = current_c + dc[dir];
        if(nr < 0 || nr >= n || nc < 0 || nc >= m){
            continue;
        }
        if(nr == start_r && nc == start_c){
            if(path_len >= 4){
                if(current_sum > max_sum){
                    max_sum = current_sum;
                }
            }
            continue;
        }
        if(!(visited_cells[nr] & (1 << nc))){
            visited_cells[nr] |= (1 << nc);
            dfs(start_r, start_c, nr, nc, current_sum + grid[nr][nc], path_len + 1);
            visited_cells[nr] &= ~(1 << nc);
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &grid[i][j]);
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            memset(visited_cells, 0, sizeof(visited_cells));
            visited_cells[i] |= (1 << j);
            dfs(i, j, i, j, grid[i][j], 1);
        }
    }
    printf("%lld\n", max_sum);
    return 0;
}