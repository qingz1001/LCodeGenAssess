#include <stdio.h>
#include <string.h>

int n, ans;
int map[5][7];
int temp[5][7];
int path[5][7][5];
int minx, miny, ming;

void print() {
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", path[i][0][0], path[i][0][1], path[i][0][2]);
    }
    exit(0);
}

void fall() {
    for (int i = 0; i < 5; i++) {
        int t = 6;
        for (int j = 5; j >= 0; j--) {
            if (map[i][j]) {
                temp[i][t--] = map[i][j];
            }
        }
        for (int j = 0; j <= t; j++) {
            map[i][j] = 0;
        }
        for (int j = t + 1; j < 7; j++) {
            map[i][j] = temp[i][j];
        }
    }
}

void check() {
    int flag = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            if (map[i][j]) {
                flag = 1;
                break;
            }
        }
        if (flag) break;
    }
    if (!flag) {
        print();
    }
}

void clear() {
    for (int i = 0; i < 5; i++) {
        int flag = 0;
        for (int j = 0; j < 7; j++) {
            if (map[i][j] != 0) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            for (int j = 0; j < 7; j++) {
                map[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            if (map[i][j]) {
                if (i > 1 && map[i][j] == map[i - 1][j] && map[i][j] == map[i - 2][j]) {
                    map[i][j] = map[i - 1][j] = map[i - 2][j] = 0;
                    fall();
                }
                if (j > 1 && map[i][j] == map[i][j - 1] && map[i][j] == map[i][j - 2]) {
                    map[i][j] = map[i][j - 1] = map[i][j - 2] = 0;
                    fall();
                }
            }
        }
    }
}

void move(int x, int y, int z, int step) {
    if (step == n) {
        check();
        return;
    }
    int t = map[x][y];
    map[x][y] = map[z][y];
    map[z][y] = t;
    path[step][0][0] = x;
    path[step][0][1] = y;
    path[step][0][2] = z - x;
    clear();
    fall();
    move(x, y, z - 1, step + 1);
    move(x, y, z + 1, step + 1);
    t = map[x][y];
    map[x][y] = map[z][y];
    map[z][y] = t;
    path[step][0][0] = x;
    path[step][0][1] = y;
    path[step][0][2] = z - x;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 5; i++) {
        int t = 0;
        while (1) {
            scanf("%d", &map[i][t]);
            if (map[i][t] == 0) break;
            t++;
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            if (map[i][j]) {
                move(i, j, i + 1, 0);
                move(i, j, i - 1, 0);
            }
        }
    }
    printf("-1");
    return 0;
}