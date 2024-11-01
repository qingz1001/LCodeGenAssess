#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    char type;
    int p;
    int q;
} Command;

void processCommands(Point *points, int n, Command *commands, int m) {
    for (int i = m - 1; i >= 0; i--) {
        if (commands[i].type == 'm') {
            for (int j = 0; j < n; j++) {
                points[j].x += commands[i].p;
                points[j].y += commands[i].q;
            }
        } else if (commands[i].type == 'x') {
            for (int j = 0; j < n; j++) {
                points[j].x = -points[j].x;
            }
        } else if (commands[i].type == 'y') {
            for (int j = 0; j < n; j++) {
                points[j].y = -points[j].y;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Point *points = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    Command *commands = (Command *)malloc(m * sizeof(Command));
    for (int i = 0; i < m; i++) {
        char type;
        scanf(" %c", &type);
        if (type == 'm') {
            int p, q;
            scanf("%d %d", &p, &q);
            commands[i].type = type;
            commands[i].p = p;
            commands[i].q = q;
        } else {
            commands[i].type = type;
            commands[i].p = 0;
            commands[i].q = 0;
        }
    }

    processCommands(points, n, commands, m);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", points[i].x, points[i].y);
    }

    free(points);
    free(commands);

    return 0;
}