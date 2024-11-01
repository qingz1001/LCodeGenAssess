#include <stdio.h>
#include <stdlib.h>

int N;
int grid[81];
char visited[81];
int max_sum = -2147483648;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void dfs(int pos, int sum) {
    if(sum > max_sum) {
        max_sum = sum;
    }
    int x = pos / N;
    int y = pos % N;
    for(int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if(nx >=0 && nx < N && ny >=0 && ny < N){
            int npos = nx * N + ny;
            if(!visited[npos]){
                visited[npos] = 1;
                dfs(npos, sum + grid[npos]);
                visited[npos] = 0;
            }
        }
    }
}

int main(){
    if(scanf("%d", &N)!=1){
        return 0;
    }
    for(int i=0; i<N*N; i++){
        if(scanf("%d", &grid[i])!=1){
            grid[i] = 0;
        }
    }
    for(int pos=0; pos<N*N; pos++){
        visited[pos] = 1;
        dfs(pos, grid[pos]);
        visited[pos] = 0;
    }
    printf("%d\n", max_sum);
    return 0;
}