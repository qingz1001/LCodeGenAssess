#include <stdio.h>

#define MAX_N 100
#define MAX_M 100

char matrix[MAX_N][MAX_M];
int n, m;

int count_rectangles() {
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '*') {
                int width = 0, height = 0;
                
                // Find width
                while (j + width < m && matrix[i][j + width] == '*') {
                    width++;
                }
                
                // Find height
                while (i + height < n && matrix[i + height][j] == '*') {
                    height++;
                }
                
                // Check if it's a valid rectangle
                int valid = 1;
                for (int x = i; x < i + height && valid; x++) {
                    for (int y = j; y < j + width && valid; y++) {
                        if (matrix[x][y] != '*') {
                            valid = 0;
                        }
                    }
                }
                
                if (valid) {
                    count++;
                    // Mark the rectangle as counted
                    for (int x = i; x < i + height; x++) {
                        for (int y = j; y < j + width; y++) {
                            matrix[x][y] = '.';
                        }
                    }
                }
            }
        }
    }
    
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }
    
    int result = count_rectangles();
    printf("%d\n", result);
    
    return 0;
}