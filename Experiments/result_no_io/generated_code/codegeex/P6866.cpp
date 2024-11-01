#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char matrix[n][m];
    int count = 0;

    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '*') {
                if (i > 0 && matrix[i-1][j] == '*') {
                    if (j > 0 && matrix[i][j-1] == '*') {
                        if (matrix[i-1][j-1] == '.') {
                            count++;
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}