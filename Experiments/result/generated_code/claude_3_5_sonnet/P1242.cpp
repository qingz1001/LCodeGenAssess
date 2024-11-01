#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 45
#define MAX_M 200000

typedef struct {
    int disk;
    char from;
    char to;
} Move;

int n;
int initial[3][MAX_N], target[3][MAX_N];
int top[3], ttop[3];
Move moves[MAX_M];
int move_count = 0;

void read_state(int state[3][MAX_N], int tops[3]) {
    for (int i = 0; i < 3; i++) {
        int j = 0;
        while (1) {
            int x;
            scanf("%d", &x);
            if (x == 0) break;
            state[i][j++] = x;
        }
        tops[i] = j;
    }
}

void move(int disk, char from, char to) {
    printf("move %d from %c to %c\n", disk, from, to);
    moves[move_count++] = (Move){disk, from, to};
}

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        move(1, from, to);
        return;
    }
    hanoi(n - 1, from, aux, to);
    move(n, from, to);
    hanoi(n - 1, aux, to, from);
}

int main() {
    scanf("%d", &n);
    
    read_state(initial, top);
    read_state(target, ttop);

    for (int i = n; i >= 1; i--) {
        int src = -1, dst = -1;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < top[j]; k++) {
                if (initial[j][k] == i) {
                    src = j;
                    break;
                }
            }
            for (int k = 0; k < ttop[j]; k++) {
                if (target[j][k] == i) {
                    dst = j;
                    break;
                }
            }
            if (src != -1 && dst != -1) break;
        }
        if (src != dst) {
            int aux = 3 - src - dst;
            hanoi(i, 'A' + src, 'A' + dst, 'A' + aux);
        }
    }

    printf("%d\n", move_count);
    return 0;
}