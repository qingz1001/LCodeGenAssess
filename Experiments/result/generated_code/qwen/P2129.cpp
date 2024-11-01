#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500001

typedef struct {
    int x, y;
} Point;

Point armies[MAX_N];
char commands[MAX_N][2];
int command_count = 0;

void process_command(char c) {
    if (c == 'm') {
        int p, q;
        scanf("%d %d", &p, &q);
        for (int i = 0; i < command_count; i++) {
            armies[i].x += p;
            armies[i].y += q;
        }
    } else if (c == 'x') {
        for (int i = 0; i < command_count; i++) {
            armies[i].x = -armies[i].x;
        }
    } else if (c == 'y') {
        for (int i = 0; i < command_count; i++) {
            armies[i].y = -armies[i].y;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &armies[i].x, &armies[i].y);
    }

    for (int i = 0; i < m; i++) {
        scanf(" %c", &commands[i]);
        process_command(commands[i]);
        command_count++;
    }

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", armies[i].x, armies[i].y);
    }

    return 0;
}