#include <stdio.h>
#include <string.h>

#define MAXN 100

int N, M;
char grid[MAXN][MAXN];
char colors[27];

void print_grid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

void fill(int x, int y, char color) {
    grid[x][y] = color;
    if (x > 0 && grid[x-1][y] == '*') fill(x-1, y, color);
    if (y > 0 && grid[x][y-1] == '*') fill(x, y-1, color);
    if (x < N-1 && grid[x+1][y] == '*') fill(x+1, y, color);
    if (y < M-1 && grid[x][y+1] == '*') fill(x, y+1, color);
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '*') {
                for (int k = 0; k < 26; k++) {
                    char color = colors[k];
                    if (i > 0 && grid[i-1][j] == color) continue;
                    if (j > 0 && grid[i][j-1] == color) continue;
                    fill(i, j, color);
                    break;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            grid[i][j] = '*';
        }
    }
    for (int i = 0; i < 26; i++) {
        colors[i] = 'a' + i;
    }
    solve();
    print_grid();
    return 0;
}