#include <stdio.h>

int main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);

    int bomb_rounds[x][4];
    for (int i = 0; i < x; i++) {
        scanf("%d %d %d %d", &bomb_rounds[i][0], &bomb_rounds[i][1], &bomb_rounds[i][2], &bomb_rounds[i][3]);
    }

    for (int i = 0; i < y; i++) {
        int key_x, key_y;
        scanf("%d %d", &key_x, &key_y);

        int count = 0;
        int last_round = -1;

        for (int j = 0; j < x; j++) {
            if (key_x >= bomb_rounds[j][0] && key_x <= bomb_rounds[j][2] &&
                key_y >= bomb_rounds[j][1] && key_y <= bomb_rounds[j][3]) {
                count++;
                last_round = j + 1;
            }
        }

        if (count > 0) {
            printf("Y %d %d\n", count, last_round);
        } else {
            printf("N\n");
        }
    }

    return 0;
}