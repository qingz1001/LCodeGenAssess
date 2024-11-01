#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int x1, y1, x2, y2;
    scanf("%d %d", &x1, &y1);
    scanf("%d %d", &x2, &y2);
    int T;
    scanf("%d", &T);
    char wind[T];
    for (int i = 0; i < T; i++) {
        scanf(" %c", &wind[i]);
    }

    int steps = 0;
    int dx = x2 - x1;
    int dy = y2 - y1;

    for (int i = 0; i < T && (dx != 0 || dy != 0); i++) {
        if ((wind[i] == 'E' && dx > 0) || (wind[i] == 'S' && dy > 0) ||
            (wind[i] == 'W' && dx < 0) || (wind[i] == 'N' && dy < 0)) {
            if (wind[i] == 'E') dx--;
            else if (wind[i] == 'S') dy--;
            else if (wind[i] == 'W') dx++;
            else if (wind[i] == 'N') dy++;
            steps++;
        }
    }

    if (dx == 0 && dy == 0) {
        printf("%d\n", steps);
    } else {
        printf("-1\n");
    }

    return 0;
}