#include <stdio.h>
#include <string.h>

#define MAX_N 100

int n;
char matrix[MAX_N][MAX_N];
char word[256];

void markWord(int x, int y, char dir) {
    int dx = 0, dy = 0;
    if (dir == 'U') dx = -1;
    else if (dir == 'D') dx = 1;
    else if (dir == 'L') dy = -1;
    else if (dir == 'R') dy = 1;
    else if (dir == 'UL') { dx = -1; dy = -1; }
    else if (dir == 'UR') { dx = -1; dy = 1; }
    else if (dir == 'DL') { dx = 1; dy = -1; }
    else if (dir == 'DR') { dx = 1; dy = 1; }

    for (int i = 0; i < strlen(word); i++) {
        matrix[x + i * dx][y + i * dy] = word[i];
    }
}

int checkWord(int x, int y, char dir) {
    int dx = 0, dy = 0;
    if (dir == 'U') dx = -1;
    else if (dir == 'D') dx = 1;
    else if (dir == 'L') dy = -1;
    else if (dir == 'R') dy = 1;
    else if (dir == 'UL') { dx = -1; dy = -1; }
    else if (dir == 'UR') { dx = -1; dy = 1; }
    else if (dir == 'DL') { dx = 1; dy = -1; }
    else if (dir == 'DR') { dx = 1; dy = 1; }

    for (int i = 0; i < strlen(word); i++) {
        if (x + i * dx < 0 || x + i * dx >= n || y + i * dy < 0 || y + i * dy >= n || matrix[x + i * dx][y + i * dy] != word[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &matrix[i][j]);
        }
    }
    scanf("%s", word);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (checkWord(i, j, 'U')) markWord(i, j, 'U');
            if (checkWord(i, j, 'D')) markWord(i, j, 'D');
            if (checkWord(i, j, 'L')) markWord(i, j, 'L');
            if (checkWord(i, j, 'R')) markWord(i, j, 'R');
            if (checkWord(i, j, 'UL')) markWord(i, j, 'UL');
            if (checkWord(i, j, 'UR')) markWord(i, j, 'UR');
            if (checkWord(i, j, 'DL')) markWord(i, j, 'DL');
            if (checkWord(i, j, 'DR')) markWord(i, j, 'DR');
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}