#include <stdio.h>
#include <stdlib.h>

int main() {
    int r;
    scanf("%d", &r);
    
    int **triangle = (int **)malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++) {
        triangle[i] = (int *)malloc((i + 1) * sizeof(int));
    }
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }
    
    for (int i = r - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            triangle[i][j] += (triangle[i + 1][j] > triangle[i + 1][j + 1]) ? triangle[i + 1][j] : triangle[i + 1][j + 1];
        }
    }
    
    printf("%d\n", triangle[0][0]);
    
    for (int i = 0; i < r; i++) {
        free(triangle[i]);
    }
    free(triangle);
    
    return 0;
}