#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 30

void fillCircle(int n, int matrix[MAX_SIZE][MAX_SIZE]) {
    int visited[MAX_SIZE][MAX_SIZE] = {0};
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int x, y;

    // Find the starting point of the closed circle
    for (x = 0; x < n; x++) {
        for (y = 0; y < n; y++) {
            if (matrix[x][y] == 1) {
                goto found;
            }
        }
    }

found:
    // Perform DFS to mark all points in the closed circle
    stack<int> s;
    s.push(x * n + y);
    while (!s.empty()) {
        int pos = s.top();
        s.pop();
        x = pos / n;
        y = pos % n;
        if (visited[x][y] || matrix[x][y] != 0) continue;
        visited[x][y] = 1;
        for (int i = 0; i < 4; i++) {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny] && matrix[nx][ny] == 0) {
                s.push(nx * n + ny);
            }
        }
    }

    // Fill the closed circle with 2
    for (x = 0; x < n; x++) {
        for (y = 0; y < n; y++) {
            if (visited[x][y] && matrix[x][y] == 0) {
                matrix[x][y] = 2;
            }
        }
    }
}

int main() {
    int n;
    int matrix[MAX_SIZE][MAX_SIZE];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    fillCircle(n, matrix);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}