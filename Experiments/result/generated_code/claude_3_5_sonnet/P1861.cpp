#include <stdio.h>
#include <string.h>

#define MAX_N 200
#define MAX_M 200

int n, m;
int ini[MAX_N][MAX_M], fin[MAX_N][MAX_M];
int diff[MAX_N][MAX_M];
int row_sum[MAX_N], col_sum[MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &ini[i][j]);
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &fin[i][j]);
            diff[i][j] = fin[i][j] - ini[i][j];
            row_sum[i] += diff[i][j];
            col_sum[j] += diff[i][j];
        }
    }
    
    long long result = 0;
    
    for (int i = 0; i < n; i++) {
        long long row_pos = 0, row_neg = 0;
        for (int j = 0; j < m; j++) {
            if (diff[i][j] > 0) row_pos += diff[i][j];
            else row_neg -= diff[i][j];
        }
        result += row_pos * (row_pos - 1) / 2;
    }
    
    for (int j = 0; j < m; j++) {
        long long col_pos = 0, col_neg = 0;
        for (int i = 0; i < n; i++) {
            if (diff[i][j] > 0) col_pos += diff[i][j];
            else col_neg -= diff[i][j];
        }
        result += col_pos * (col_pos - 1) / 2;
    }
    
    printf("%lld\n", result);
    
    return 0;
}