#include <stdio.h>
#include <stdlib.h>

#define MAXN 500001

typedef struct {
    int x, y;
} Position;

Position army[MAXN];
char commands[MAXN];
int commandCount = 0;

void move(int dx, int dy) {
    for (int i = 0; i < commandCount; i++) {
        if (commands[i] == 'm') {
            scanf("%d %d", &army[i].x, &army[i].y);
            army[i].x += dx;
            army[i].y += dy;
        } else if (commands[i] == 'x') {
            army[i].x *= -1;
        } else if (commands[i] == 'y') {
            army[i].y *= -1;
        }
    }
}

void processCommands() {
    for (int i = commandCount - 1; i >= 0; i--) {
        char c = commands[i];
        if (c == 'm') {
            int p, q;
            scanf("%d %d", &p, &q);
            move(p, q);
        } else if (c == 'x') {
            move(0, 0);
        } else if (c == 'y') {
            move(0, 0);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &army[i].x, &army[i].y);
    }

    for (int i = 0; i < m; i++) {
        scanf(" %c", &commands[commandCount++]);
    }

    processCommands();

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", army[i].x, army[i].y);
    }

    return 0;
}