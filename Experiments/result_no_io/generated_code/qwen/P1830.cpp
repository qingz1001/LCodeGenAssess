#include <stdio.h>

#define MAX_N 105
#define MAX_M 105
#define MAX_X 105
#define MAX_Y 105

int bombed[MAX_N][MAX_M];
int bomb_count[MAX_N][MAX_M];

void mark_bomb(int x1, int y1, int x2, int y2, int round) {
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            bombed[i][j] = 1;
            bomb_count[i][j] = round;
        }
    }
}

int main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);

    for (int i = 1; i <= x; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        mark_bomb(x1, y1, x2, y2, i);
    }

    for (int i = 1; i <= y; i++) {
        int px, py;
        scanf("%d %d", &px, &py);
        if (bombed[px][py]) {
            printf("Y %d %d\n", bomb_count[px][py], bombed[px][py]);
        } else {
            printf("N\n");
        }
    }

    return 0;
}