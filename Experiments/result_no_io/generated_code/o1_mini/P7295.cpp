#include <stdio.h>
#include <string.h>

#define MAXN 1001
#define MAXC 26

int main(){
    int N, M, Q;
    scanf("%d %d %d", &N, &M, &Q);
    
    char grid[MAXN][MAXN];
    for(int i=1;i<=N;i++){
        scanf("%s", grid[i]+1);
    }
    
    // Initialize prefix sums for each color
    long long sum_cell[MAXC][MAXN][MAXN];
    long long sum_h[MAXC][MAXN][MAXN];
    long long sum_v[MAXC][MAXN][MAXN];
    
    // Initialize to zero
    for(int c=0;c<MAXC;c++){
        for(int i=0;i<=N;i++){
            for(int j=0;j<=M;j++){
                sum_cell[c][i][j] = 0;
                sum_h[c][i][j] = 0;
                sum_v[c][i][j] = 0;
            }
        }
    }
    
    // Compute sum_cell
    for(int c=0;c<MAXC;c++){
        for(int i=1;i<=N;i++){
            for(int j=1;j<=M;j++){
                sum_cell[c][i][j] = sum_cell[c][i-1][j] + sum_cell[c][i][j-1] - sum_cell[c][i-1][j-1];
                if(grid[i][j]-'A' == c){
                    sum_cell[c][i][j]++;
                }
            }
        }
    }
    
    // Compute sum_h
    for(int c=0;c<MAXC;c++){
        for(int i=1;i<=N;i++){
            for(int j=1;j<=M;j++){
                sum_h[c][i][j] = sum_h[c][i-1][j] + sum_h[c][i][j-1] - sum_h[c][i-1][j-1];
                if(j < M && (grid[i][j]-'A' == c) && (grid[i][j+1]-'A' == c)){
                    sum_h[c][i][j]++;
                }
            }
        }
    }
    
    // Compute sum_v
    for(int c=0;c<MAXC;c++){
        for(int i=1;i<=N;i++){
            for(int j=1;j<=M;j++){
                sum_v[c][i][j] = sum_v[c][i-1][j] + sum_v[c][i][j-1] - sum_v[c][i-1][j-1];
                if(i < N && (grid[i][j]-'A' == c) && (grid[i+1][j]-'A' == c)){
                    sum_v[c][i][j]++;
                }
            }
        }
    }
    
    // Process queries
    while(Q--){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        long long total_strokes =0;
        for(int c=0;c<MAXC;c++){
            // Number of cells with color c
            long long cells = sum_cell[c][x2][y2] - sum_cell[c][x1-1][y2] - sum_cell[c][x2][y1-1] + sum_cell[c][x1-1][y1-1];
            if(cells ==0) continue;
            // Number of horizontal adjacents
            long long adj_h = sum_h[c][x2][y2-1] - sum_h[c][x1-1][y2-1] - sum_h[c][x2][y1-1] + sum_h[c][x1-1][y1-1];
            // Number of vertical adjacents
            long long adj_v = sum_v[c][x2-1][y2] - sum_v[c][x1-1][y2] - sum_v[c][x2-1][y1-1] + sum_v[c][x1-1][y1-1];
            // Connected components for color c
            total_strokes += (cells - adj_h - adj_v);
        }
        printf("%lld\n", total_strokes);
    }
    
    return 0;
}