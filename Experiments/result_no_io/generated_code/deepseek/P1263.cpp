#include <stdio.h>
#include <stdbool.h>

#define MAX 200

int m, n;
int castle[MAX][MAX];
bool visited[MAX][MAX];
int guards[MAX][2];
int guard_count = 0;

bool is_valid(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n && castle[x][y] == 0 && !visited[x][y];
}

bool dfs(int x, int y) {
    if (!is_valid(x, y)) return false;

    visited[x][y] = true;

    // Check right
    for (int i = y + 1; i < n; i++) {
        if (castle[x][i] == 2) break;
        if (castle[x][i] == 0 && !visited[x][i]) {
            if (dfs(x, i)) {
                guards[guard_count][0] = x + 1;
                guards[guard_count][1] = y + 1;
                guard_count++;
                return true;
            }
        }
    }

    // Check left
    for (int i = y - 1; i >= 0; i--) {
        if (castle[x][i] == 2) break;
        if (castle[x][i] == 0 && !visited[x][i]) {
            if (dfs(x, i)) {
                guards[guard_count][0] = x + 1;
                guards[guard_count][1] = y + 1;
                guard_count++;
                return true;
            }
        }
    }

    // Check down
    for (int i = x + 1; i < m; i++) {
        if (castle[i][y] == 2) break;
        if (castle[i][y] == 0 && !visited[i][y]) {
            if (dfs(i, y)) {
                guards[guard_count][0] = x + 1;
                guards[guard_count][1] = y + 1;
                guard_count++;
                return true;
            }
        }
    }

    // Check up
    for (int i = x - 1; i >= 0; i--) {
        if (castle[i][y] == 2) break;
        if (castle[i][y] == 0 && !visited[i][y]) {
            if (dfs(i, y)) {
                guards[guard_count][0] = x + 1;
                guards[guard_count][1] = y + 1;
                guard_count++;
                return true;
            }
        }
    }

    return false;
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &castle[i][j]);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (castle[i][j] == 0 && !visited[i][j]) {
                if (dfs(i, j)) {
                    guards[guard_count][0] = i + 1;
                    guards[guard_count][1] = j + 1;
                    guard_count++;
                }
            }
        }
    }

    printf("%d\n", guard_count);
    for (int i = 0; i < guard_count; i++) {
        printf("%d %d\n", guards[i][0], guards[i][1]);
    }

    return 0;
}