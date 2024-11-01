#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000
#define MAX_M 500000

typedef struct {
    int x, y;
} Position;

typedef struct {
    char command;
    int p, q;
} Operation;

Position positions[MAX_N];
Operation operations[MAX_M];

void applyOperation(Position *pos, Operation op) {
    switch(op.command) {
        case 'm':
            pos->x += op.p;
            pos->y += op.q;
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
        scanf(" %c", &operations[i].command);
        if (operations[i].command == 'm') {
            scanf("%d %d", &operations[i].p, &operations[i].q);
        }
    }

    for (int i = m - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            applyOperation(&positions[j], operations[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", positions[i].x, positions[i].y);
    }

    return 0;
}