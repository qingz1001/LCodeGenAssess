#include <stdio.h>
#include <string.h>

#define MAX_N 18
#define INF 1000000000

int n;
int matrix[MAX_N][MAX_N];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

int count_surrounding_males(int x, int y) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (is_valid(nx, ny) && matrix[nx][ny] == 1) {
            count++;
        }
    }
    return count;
}

int solve() {
    int changes = 0;
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    int males = count_surrounding_males(i, j);
                    if (males % 2 == 1) {
                        matrix[i][j] = 1;
                        changes++;
                        changed = 1;
                    }
                }
            }
        }
    } while (changed);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (count_surrounding_males(i, j) % 2 != 0) {
                return -1;
            }
        }
    }

    return changes;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int result = solve();
    printf("%d\n", result);

    return 0;
}