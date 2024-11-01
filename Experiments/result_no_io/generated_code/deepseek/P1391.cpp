#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 18

int n;
int matrix[MAXN][MAXN];
int min_changes = INT_MAX;

int count_neighbors(int x, int y) {
    int count = 0;
    if (x > 0 && matrix[x-1][y] == 1) count++;
    if (x < n-1 && matrix[x+1][y] == 1) count++;
    if (y > 0 && matrix[x][y-1] == 1) count++;
    if (y < n-1 && matrix[x][y+1] == 1) count++;
    return count;
}

void dfs(int x, int y, int changes) {
    if (x == n) {
        min_changes = changes < min_changes ? changes : min_changes;
        return;
    }

    int next_x = y == n-1 ? x + 1 : x;
    int next_y = y == n-1 ? 0 : y + 1;

    dfs(next_x, next_y, changes);

    matrix[x][y] = 1;
    int new_changes = changes + 1;
    int valid = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1 && count_neighbors(i, j) % 2 != 0) {
                valid = 0;
                break;
            }
        }
        if (!valid) break;
    }
    if (valid) dfs(next_x, next_y, new_changes);
    matrix[x][y] = 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    dfs(0, 0, 0);

    if (min_changes == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", min_changes);
    }

    return 0;
}