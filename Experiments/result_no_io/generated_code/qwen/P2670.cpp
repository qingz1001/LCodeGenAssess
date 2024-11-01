#include <stdio.h>

#define MAXN 105

int n, m;
char grid[MAXN][MAXN];
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void process() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '*') continue;
            int count = 0;
            for (int k = 0; k < 8; k++) {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == '*') {
                    count++;
                }
            }
            grid[i][j] = '0' + count;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    process();
    for (int i = 0; i < n; i++) {
        printf("%s\n", grid[i]);
    }
    return 0;
}