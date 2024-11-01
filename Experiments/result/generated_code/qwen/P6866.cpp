#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    char matrix[101][101];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %c", &matrix[i][j]);
        }
    }
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '*') {
                // Check if it's the top-left corner of a rectangle
                bool isTopLeft = true;
                for (int k = 0; k <= i && isTopLeft; k++) {
                    for (int l = 0; l <= j && isTopLeft; l++) {
                        if ((k != i || l != j) && matrix[k][l] == '*') {
                            isTopLeft = false;
                        }
                    }
                }
                if (isTopLeft) {
                    count++;
                }
            }
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}