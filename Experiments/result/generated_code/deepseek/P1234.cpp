#include <stdio.h>
#include <string.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char matrix[n][m + 1];

    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }

    int count = 0;

    // Check horizontally
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m - 4; j++) {
            if (strncmp(&matrix[i][j], "hehe", 4) == 0) {
                count++;
            }
        }
    }

    // Check vertically
    for (int i = 0; i <= n - 4; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 'h' && matrix[i + 1][j] == 'e' && matrix[i + 2][j] == 'h' && matrix[i + 3][j] == 'e') {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}