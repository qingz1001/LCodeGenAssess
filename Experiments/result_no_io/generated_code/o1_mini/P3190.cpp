#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100
#define MAX_M 6

int n, m;
int grid[MAX_N][MAX_M];
long long max_sum = LLONG_MIN;
int visited_rows[MAX_N];
int directions[4][2] = { { -1,0 }, { 1,0 }, { 0,-1 }, { 0,1 } };

void dfs(int x, int y, long long current_sum, int step, int start_x, int start_y) {
    for(int d=0; d<4; d++) {
        int nx = x + directions[d][0];
        int ny = y + directions[d][1];
        if(nx == start_x && ny == start_y) {
            if(step >=4) {
                if(current_sum > max_sum) {
                    max_sum = current_sum;
                }
            }
            continue;
        }
        if(nx >=0 && nx < n && ny >=0 && ny < m) {
            if( (visited_rows[nx] & (1 << ny)) == 0 ) {
                visited_rows[nx] |= (1 << ny);
                dfs(nx, ny, current_sum + grid[nx][ny], step +1, start_x, start_y);
                visited_rows[nx] &= ~(1 << ny);
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    for(int i=0;i<n;i++) {
        for(int j=0; j<m; j++) {
            // Initialize visited
            for(int k=0; k<n; k++) {
                visited_rows[k] = 0;
            }
            visited_rows[i] |= (1 << j);
            dfs(i, j, grid[i][j], 1, i, j);
        }
    }
    printf("%lld\n", max_sum);
    return 0;
}