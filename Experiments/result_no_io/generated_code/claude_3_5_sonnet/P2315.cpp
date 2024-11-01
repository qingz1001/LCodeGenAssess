#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001

int n;
int grid[MAX_N][MAX_N];
int row_sum[MAX_N][MAX_N];
int col_sum[MAX_N][MAX_N];

int main() {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    
    fscanf(fin, "%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fscanf(fin, "%d", &grid[i][j]);
        }
    }
    
    // Calculate prefix sums
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            row_sum[i][j] = row_sum[i][j-1] + grid[i][j];
            col_sum[i][j] = col_sum[i-1][j] + grid[i][j];
        }
    }
    
    long long count = 0;
    
    // Enumerate all possible triangles
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = j+1; k <= n; k++) {
                if (grid[i][j] && grid[i][k]) {
                    int left = j, right = k;
                    for (int l = i+1; l <= n; l++) {
                        while (left > 1 && grid[l][left-1]) left--;
                        while (right < n && grid[l][right+1]) right++;
                        if (left > right) break;
                        if (grid[l][left] && grid[l][right]) {
                            int row_points = row_sum[l][right] - row_sum[l][left-1];
                            int col_points = col_sum[l][k] - col_sum[i-1][k] + col_sum[l][j] - col_sum[i-1][j];
                            if (row_points + col_points == right - left + l - i + 3) {
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
    
    fprintf(fout, "%lld\n", count);
    
    fclose(fin);
    fclose(fout);
    return 0;
}