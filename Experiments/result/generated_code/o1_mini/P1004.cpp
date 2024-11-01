#include <stdio.h>
#include <string.h>

int N;
int grid[9][9];
int dp_grid[9][9];
int max_total = 0;

// Function to compute the maximum path sum using DP
int compute_max_path() {
    dp_grid[0][0] = grid[0][0];
    for(int c = 1; c < N; c++) {
        dp_grid[0][c] = dp_grid[0][c-1] + grid[0][c];
    }
    for(int r = 1; r < N; r++) {
        dp_grid[r][0] = dp_grid[r-1][0] + grid[r][0];
        for(int c = 1; c < N; c++) {
            if(dp_grid[r-1][c] > dp_grid[r][c-1])
                dp_grid[r][c] = grid[r][c] + dp_grid[r-1][c];
            else
                dp_grid[r][c] = grid[r][c] + dp_grid[r][c-1];
        }
    }
    return dp_grid[N-1][N-1];
}

// Recursive function to explore all path1 and compute corresponding path2
void search(int r, int c, int sum1) {
    sum1 += grid[r][c];
    int tmp = grid[r][c];
    grid[r][c] = 0;

    if(r == N-1 && c == N-1){
        int sum2 = compute_max_path();
        if(sum1 + sum2 > max_total)
            max_total = sum1 + sum2;
    }
    else{
        if(c + 1 < N)
            search(r, c+1, sum1);
        if(r + 1 < N)
            search(r+1, c, sum1);
    }

    grid[r][c] = tmp;
}

int main(){
    // Read N
    scanf("%d", &N);
    // Initialize grid to 0
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            grid[i][j] = 0;
    // Read grid values
    while(1){
        int x, y, val;
        scanf("%d %d %d", &x, &y, &val);
        if(x == 0 && y == 0 && val == 0)
            break;
        if(x >=1 && x <=N && y >=1 && y <=N)
            grid[x-1][y-1] = val;
    }
    // Start searching from (0,0)
    search(0, 0, 0);
    // Output the result
    printf("%d\n", max_total);
    return 0;
}