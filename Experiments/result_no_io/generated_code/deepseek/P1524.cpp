#include <stdio.h>
#include <stdbool.h>

#define MAXN 200
#define MAXM 200

char front[MAXN][MAXM];
char back[MAXN][MAXM];
bool visited[MAXN][MAXM];
int N, M;

void dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M || visited[x][y]) return;
    visited[x][y] = true;

    if (front[x][y] == '/') {
        if (x > 0 && y < M - 1 && front[x - 1][y + 1] == '\\') dfs(x - 1, y + 1);
        if (x < N - 1 && y > 0 && front[x + 1][y - 1] == '\\') dfs(x + 1, y - 1);
    } else if (front[x][y] == '\\') {
        if (x > 0 && y > 0 && front[x - 1][y - 1] == '/') dfs(x - 1, y - 1);
        if (x < N - 1 && y < M - 1 && front[x + 1][y + 1] == '/') dfs(x + 1, y + 1);
    } else if (front[x][y] == 'X') {
        if (x > 0 && y > 0 && front[x - 1][y - 1] == '/') dfs(x - 1, y - 1);
        if (x > 0 && y < M - 1 && front[x - 1][y + 1] == '\\') dfs(x - 1, y + 1);
        if (x < N - 1 && y > 0 && front[x + 1][y - 1] == '\\') dfs(x + 1, y - 1);
        if (x < N - 1 && y < M - 1 && front[x + 1][y + 1] == '/') dfs(x + 1, y + 1);
    }

    if (back[x][y] == '/') {
        if (x > 0 && y < M - 1 && back[x - 1][y + 1] == '\\') dfs(x - 1, y + 1);
        if (x < N - 1 && y > 0 && back[x + 1][y - 1] == '\\') dfs(x + 1, y - 1);
    } else if (back[x][y] == '\\') {
        if (x > 0 && y > 0 && back[x - 1][y - 1] == '/') dfs(x - 1, y - 1);
        if (x < N - 1 && y < M - 1 && back[x + 1][y + 1] == '/') dfs(x + 1, y + 1);
    } else if (back[x][y] == 'X') {
        if (x > 0 && y > 0 && back[x - 1][y - 1] == '/') dfs(x - 1, y - 1);
        if (x > 0 && y < M - 1 && back[x - 1][y + 1] == '\\') dfs(x - 1, y + 1);
        if (x < N - 1 && y > 0 && back[x + 1][y - 1] == '\\') dfs(x + 1, y - 1);
        if (x < N - 1 && y < M - 1 && back[x + 1][y + 1] == '/') dfs(x + 1, y + 1);
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", front[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%s", back[i]);
    }

    int needleCount = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!visited[i][j] && (front[i][j] != '.' || back[i][j] != '.')) {
                dfs(i, j);
                needleCount++;
            }
        }
    }

    printf("%d\n", needleCount);
    return 0;
}