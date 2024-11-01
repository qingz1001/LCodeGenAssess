#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000
#define MAX_M 500000

typedef struct {
    int x, y;
} Position;

typedef struct {
    char type;
    int p, q;
} Command;

Position positions[MAX_N];
Command commands[MAX_M];

void executeCommand(Position *pos, Command cmd) {
    switch (cmd.type) {
        case 'm':
            pos->x += cmd.p;
            pos->y += cmd.q;
            break;
        case 'x':
            pos->x = -pos->x;
            break;
        case 'y':
            pos->y = -pos->y;
            break;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &positions[i].x, &positions[i].y);
    }

    for (int i = 0; i < m; i++) {
        scanf(" %c", &commands[i].type);
        if (commands[i].type == 'm') {
            scanf("%d %d", &commands[i].p, &commands[i].q);
        }
    }

    for (int i = m - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            executeCommand(&positions[j], commands[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", positions[i].x, positions[i].y);
    }

    return 0;
}