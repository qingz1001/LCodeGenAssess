#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 200

int m, n;
int grid[MAX][MAX];
bool visited[MAX][MAX];
int guards[MAX][2];
int guard_count = 0;

bool is_valid(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 0 && !visited[x][y];
}

void place_guards(int x, int y) {
    guards[guard_count][0] = x + 1;
    guards[guard_count][1] = y + 1;
    guard_count++;
    visited[x][y] = true;

    // Mark all cells in the same row and column as visited
    for (int i = 0; i < m; i++) {
        visited[i][y] = true;
    }
    for (int j = 0; j < n; j++) {
        visited[x][j] = true;
    }
}

int main() {
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
            visited[i][j] = (grid[i][j] != 0);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (is_valid(i, j)) {
                place_guards(i, j);
            }
        }
    }

    printf("%d\n", guard_count);
    for (int i = 0; i < guard_count; i++) {
        printf("%d %d\n", guards[i][0], guards[i][1]);
    }

    return 0;
}