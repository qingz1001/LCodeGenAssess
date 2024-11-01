#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    char **matrix = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (char *)malloc(m * sizeof(char));
        scanf(" %s", matrix[i]);
    }
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '*') {
                int x = i + 1;
                while (x < n && matrix[x][j] != '*') x++;
                int y = j + 1;
                while (y < m && matrix[i][y] != '*') y++;
                count += (x - i) * (y - j);
                i = x - 1;
                j = y - 1;
            }
        }
    }
    
    printf("%d\n", count);
    
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}