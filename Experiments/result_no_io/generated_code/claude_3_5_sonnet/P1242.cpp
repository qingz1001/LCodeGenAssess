#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 45
#define MAX_STEPS 1000000

typedef struct {
    int disks[MAX_N];
    int top;
} Stack;

Stack initial[3], goal[3], current[3];
int n, steps;
char moves[MAX_STEPS][20];

void push(Stack *s, int disk) {
    s->disks[s->top++] = disk;
}

int pop(Stack *s) {
    return s->disks[--s->top];
}

void move_disk(int disk, int from, int to) {
    pop(&current[from]);
    push(&current[to], disk);
    sprintf(moves[steps++], "move %d from %c to %c", disk, 'A' + from, 'A' + to);
}

int is_valid_move(int from, int to) {
    if (current[from].top == 0) return 0;
    if (current[to].top == 0) return 1;
    return current[from].disks[current[from].top - 1] < current[to].disks[current[to].top - 1];
}

int is_goal_state() {
    for (int i = 0; i < 3; i++) {
        if (current[i].top != goal[i].top) return 0;
        for (int j = 0; j < current[i].top; j++) {
            if (current[i].disks[j] != goal[i].disks[j]) return 0;
        }
    }
    return 1;
}

void solve() {
    while (!is_goal_state()) {
        for (int from = 0; from < 3; from++) {
            for (int to = 0; to < 3; to++) {
                if (from != to && is_valid_move(from, to)) {
                    int disk = current[from].disks[current[from].top - 1];
                    move_disk(disk, from, to);
                    if (is_goal_state()) return;
                }
            }
        }
    }
}

void read_state(Stack state[]) {
    for (int i = 0; i < 3; i++) {
        state[i].top = 0;
        int disk;
        while (scanf("%d", &disk) == 1 && disk != 0) {
            push(&state[i], disk);
        }
    }
}

int main() {
    scanf("%d", &n);
    read_state(initial);
    read_state(goal);

    memcpy(current, initial, sizeof(initial));

    steps = 0;
    solve();

    for (int i = 0; i < steps; i++) {
        printf("%s\n", moves[i]);
    }
    printf("%d\n", steps);

    return 0;
}