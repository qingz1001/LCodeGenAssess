#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 45

int initial_state[MAX_DISKS + 1];
int target_state[MAX_DISKS + 1];
int temp_state[MAX_DISKS + 1];
int num_disks;
int move_count = 0;

void move(int disk, char from, char to) {
    printf("move %d from %c to %c\n", disk, from, to);
    move_count++;
}

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        if (initial_state[n] != target_state[n]) {
            move(n, from, to);
        }
        return;
    }

    hanoi(n - 1, from, aux, to);
    if (initial_state[n] != target_state[n]) {
        move(n, from, to);
    }
    hanoi(n - 1, aux, to, from);
}

int main() {
    scanf("%d", &num_disks);

    for (int i = 0; i < 3; i++) {
        int disk;
        while (scanf("%d", &disk) == 1 && disk != 0) {
            initial_state[disk] = i;
        }
    }

    for (int i = 0; i < 3; i++) {
        int disk;
        while (scanf("%d", &disk) == 1 && disk != 0) {
            target_state[disk] = i;
        }
    }

    hanoi(num_disks, 'A', 'C', 'B');

    printf("%d\n", move_count);

    return 0;
}