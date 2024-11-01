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

void applyCommand(Point *army, Command *cmd) {
    switch (cmd->type) {
        case 'm':
            army->x += cmd->p;
            army->y += cmd->q;
            break;
        case 'x':
            army->x = -army->x;
            break;
        case 'y':
            army->y = -army->y;
            break;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Point *armies = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &armies[i].x, &armies[i].y);
    }

    Command *commands = (Command *)malloc(m * sizeof(Command));
    for (int i = 0; i < m; i++) {
        char type;
        scanf(" %c", &type);
        if (type == 'm') {
            int p, q;
            scanf("%d %d", &p, &q);
            commands[i] = (Command){type, p, q};
        } else {
            commands[i] = (Command){type, 0, 0};
        }
    }

    // Apply commands in reverse order
    for (int i = m - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            applyCommand(&armies[j], &commands[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", armies[i].x, armies[i].y);
    }

    free(armies);
    free(commands);

    return 0;
}