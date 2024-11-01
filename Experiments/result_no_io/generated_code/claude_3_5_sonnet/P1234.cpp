#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 1000

char matrix[MAX_N][MAX_M + 1];

int count_hehe(int n, int m) {
    int count = 0;
    
    // 检查水平方向
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m - 4; j++) {
            if (strncmp(&matrix[i][j], "hehe", 4) == 0) {
                count++;
            }
        }
    }
    
    // 检查垂直方向
    for (int i = 0; i <= n - 4; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 'h' && matrix[i+1][j] == 'e' && 
                matrix[i+2][j] == 'h' && matrix[i+3][j] == 'e') {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }
    
    int result = count_hehe(n, m);
    printf("%d\n", result);
    
    return 0;
}