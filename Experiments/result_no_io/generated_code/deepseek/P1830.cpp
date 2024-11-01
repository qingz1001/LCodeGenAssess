#include <stdio.h>

#define MAXN 100
#define MAXM 100

int main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);

    int bomb_count[MAXN][MAXM] = {0};
    int last_bomb[MAXN][MAXM] = {0};

    for (int i = 0; i < x; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        for (int j = x1 - 1; j < x2; j++) {
            for (int k = y1 - 1; k < y2; k++) {
                bomb_count[j][k]++;
                last_bomb[j][k] = i + 1;
            }
        }
    }

    for (int i = 0; i < y; i++) {
        int px, py;
        scanf("%d %d", &px, &py);
        px--; py--;
        if (bomb_count[px][py] > 0) {
            printf("Y %d %d\n", bomb_count[px][py], last_bomb[px][py]);
        } else {
            printf("N\n");
        }
    }

    return 0;
}