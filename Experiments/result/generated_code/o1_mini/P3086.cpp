#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 300
#define LOGN 10

int main(){
    int N;
    scanf("%d", &N);
    char grid[MAXN][MAXN+1];
    for(int i=0;i<N;i++) {
        scanf("%s", grid[i]);
    }

    // Precompute up and down arrays
    int up[MAXN][MAXN];
    int down[MAXN][MAXN];
    for(int c=0; c<N; c++) {
        up[0][c] = (grid[0][c] == '.') ? 1 : 0;
        for(int r=1; r<N; r++) {
            if(grid[r][c] == '.') up[r][c] = up[r-1][c] + 1;
            else up[r][c] = 0;
        }
    }
    for(int c=0; c<N; c++) {
        down[N-1][c] = (grid[N-1][c] == '.') ? 1 : 0;
        for(int r=N-2; r>=0; r--){
            if(grid[r][c] == '.') down[r][c] = down[r+1][c] + 1;
            else down[r][c] = 0;
        }
    }

    // Precompute log2
    int log2n = 0;
    for(int i=1; i<=N; i++) {
        if((1<<log2n) == i) log2n++;
        else if((1<<log2n) > i) break;
    }
    int log_table[MAXN+1];
    log_table[1] = 0;
    for(int i=2; i<=N; i++) {
        log_table[i] = log_table[i/2] + 1;
    }

    // Build Sparse Tables for up and down
    int sparse_up[MAXN][LOGN][MAXN];
    int sparse_down[MAXN][LOGN][MAXN];
    for(int r=0; r<N; r++) {
        for(int c=0; c<N; c++) {
            sparse_up[r][0][c] = up[r][c];
            sparse_down[r][0][c] = down[r][c];
        }
        for(int k=1; (1<<k) <= N; k++) {
            for(int c=0; c + (1<<k) <= N; c++) {
                if(sparse_up[r][k-1][c] < sparse_up[r][k-1][c + (1<<(k-1))])
                    sparse_up[r][k][c] = sparse_up[r][k-1][c];
                else
                    sparse_up[r][k][c] = sparse_up[r][k-1][c + (1<<(k-1))];
                if(sparse_down[r][k-1][c] < sparse_down[r][k-1][c + (1<<(k-1))])
                    sparse_down[r][k][c] = sparse_down[r][k-1][c];
                else
                    sparse_down[r][k][c] = sparse_down[r][k-1][c + (1<<(k-1))];
            }
        }
    }

    // Function to get min in range using Sparse Table
    #define GET_MIN(table, r, l, h) ({ \
        int j = log_table[(h)-(l)+1]; \
        int min1 = table[r][j][l]; \
        int min2 = table[r][j][(h)-(1<<j)+1]; \
        min1 < min2 ? min1 : min2; \
    })

    long long max_product = -1;
    for(int r=0; r<N; r++) {
        int start = -1;
        for(int c=0; c<=N; c++) {
            if(c < N && grid[r][c] == '.') {
                if(start == -1) start = c;
            }
            else {
                if(start != -1){
                    int end = c-1;
                    for(int c1=start; c1<=end; c1++) {
                        for(int c2=c1; c2<=end; c2++) {
                            int len = c2 - c1 +1;
                            if(len < 3) continue;
                            int k = log_table[len];
                            int min_up = GET_MIN(sparse_up, r, c1, c2);
                            int min_down = GET_MIN(sparse_down, r, c1, c2);
                            if(min_up >=3 && min_down >=3){
                                int area1 = (min_up -2) * (len -2);
                                int area2 = (min_down -2) * (len -2);
                                long long product = (long long)area1 * (long long)area2;
                                if(product > max_product) max_product = product;
                            }
                        }
                    }
                    start = -1;
                }
            }
        }
    }

    printf("%lld\n", max_product);
    return 0;
}