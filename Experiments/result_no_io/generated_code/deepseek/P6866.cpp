#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int main() {
    int n, m;
    char matrix[MAX][MAX];
    bool visited[MAX][MAX] = {false};
    int rectangles = 0;

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '*' && !visited[i][j]) {
                rectangles++;
                int x = i, y = j;
                while (x < n && matrix[x][j] == '*') {
                    y = j;
                    while (y < m && matrix[x][y] == '*') {
                        visited[x][y] = true;
                        y++;
                    }
                    x++;
                }
            }
        }
    }

    printf("%d\n", rectangles);
    return 0;
}