#include <stdio.h>
#include <stdlib.h>

#define MAX_N 45

void hanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        printf("move %d from %c to %c\n", n, from_rod, to_rod);
        return;
    }
    hanoi(n - 1, from_rod, aux_rod, to_rod);
    printf("move %d from %c to %c\n", n, from_rod, to_rod);
    hanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n;
    scanf("%d", &n);

    int initial[MAX_N], target[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &initial[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &target[i]);
    }

    int moves = 0;
    for (int i = 0; i < n; i++) {
        if (initial[i] != target[i]) {
            moves++;
            hanoi(i + 1, 'A', 'C', 'B');
        }
    }

    printf("%d\n", moves);
    return 0;
}