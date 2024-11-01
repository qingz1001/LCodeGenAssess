#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

char grid[MAX][MAX];
bool visited[MAX][MAX];
int R, C;

bool isValid(int x, int y) {
    return x >= 0 && x < R && y >= 0 && y < C;
}

bool isSquare(int x, int y, int size) {
    if (!isValid(x + size - 1, y + size - 1)) return false;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[x + i][y + j] != '#') return false;
        }
    }
    return true;
}

void markVisited(int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            visited[x + i][y + j] = true;
        }
    }
}

bool checkAdjacent(int x, int y) {
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isValid(nx, ny) && grid[nx][ny] == '#' && !visited[nx][ny]) {
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        scanf("%s", grid[i]);
    }

    int shipCount = 0;
    bool badPlacement = false;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '#' && !visited[i][j]) {
                int size = 1;
                while (isSquare(i, j, size + 1)) size++;
                if (checkAdjacent(i, j)) {
                    badPlacement = true;
                    break;
                }
                markVisited(i, j, size);
                shipCount++;
            }
        }
        if (badPlacement) break;
    }

    if (badPlacement) {
        printf("Bad placement.\n");
    } else {
        printf("There are %d ships.\n", shipCount);
    }

    return 0;
}