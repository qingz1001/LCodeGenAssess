#include <stdio.h>
#include <string.h>

#define MAX_N 150

char matrix[MAX_N][MAX_N + 1];
int n;

int count_white_rectangles() {
    int count = 0;
    int left[MAX_N][MAX_N];
    
    // Initialize left array
    for (int i = 0; i < n; i++) {
        left[i][0] = (matrix[i][0] == 'W');
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == 'W') {
                left[i][j] = left[i][j-1] + 1;
            } else {
                left[i][j] = 0;
            }
        }
    }
    
    // Count rectangles
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            int width = left[i][j];
            for (int k = i; k >= 0 && left[k][j] > 0; k--) {
                if (left[k][j] < width) {
                    width = left[k][j];
                }
                count += width;
            }
        }
    }
    
    return count;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }
    
    int result = count_white_rectangles();
    printf("%d\n", result);
    
    return 0;
}