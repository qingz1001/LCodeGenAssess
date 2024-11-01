#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int x1, y1, x2, y2, T;
    scanf("%d %d", &x1, &y1);
    scanf("%d %d", &x2, &y2);
    scanf("%d", &T);

    char directions[T];
    for (int i = 0; i < T; i++) {
        scanf(" %c", &directions[i]);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = 0;
    for (int i = 0; i < T; i++) {
        if (dx > 0 && directions[i] == 'E') {
            dx--;
            steps++;
        } else if (dx < 0 && directions[i] == 'W') {
            dx++;
            steps++;
        } else if (dy > 0 && directions[i] == 'N') {
            dy--;
            steps++;
        } else if (dy < 0 && directions[i] == 'S') {
            dy++;
            steps++;
        } else {
            steps++;
        }

        if (dx == 0 && dy == 0) {
            printf("%d\n", steps);
            return 0;
        }
    }

    if (dx == 0 && dy == 0) {
        printf("%d\n", steps);
    } else {
        printf("-1\n");
    }

    return 0;
}