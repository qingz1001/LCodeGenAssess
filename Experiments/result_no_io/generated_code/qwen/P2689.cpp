#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int x1, y1, x2, y2;
    scanf("%d %d", &x1, &y1);
    scanf("%d %d", &x2, &y2);
    int T;
    scanf("%d", &T);
    char directions[T];
    for (int i = 0; i < T; i++) {
        scanf(" %c", &directions[i]);
    }

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int steps = dx + dy;

    int wind[4] = {0}; // E, S, W, N
    for (int i = 0; i < T; i++) {
        switch (directions[i]) {
            case 'E': wind[0]++; break;
            case 'S': wind[1]++; break;
            case 'W': wind[2]++; break;
            case 'N': wind[3]++; break;
        }
    }

    if (wind[0] >= dx && wind[1] >= dy) {
        printf("%d\n", steps);
    } else {
        printf("-1\n");
    }

    return 0;
}