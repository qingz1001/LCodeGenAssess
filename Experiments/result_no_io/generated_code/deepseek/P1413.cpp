#include <stdio.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 60

typedef struct {
    int row;
    int time;
} Zombie;

int compare(const void *a, const void *b) {
    Zombie *z1 = (Zombie *)a;
    Zombie *z2 = (Zombie *)b;
    if (z1->time == z2->time) {
        return z1->row - z2->row;
    }
    return z1->time - z2->time;
}

int main() {
    int n;
    scanf("%d", &n);

    Zombie zombies[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &zombies[i].row, &zombies[i].time);
    }

    qsort(zombies, n, sizeof(Zombie), compare);

    int nuts = 0;
    int last_nut_time[ROWS] = {0};

    for (int i = 0; i < n; i++) {
        int row = zombies[i].row - 1;
        int time = zombies[i].time;

        if (time > last_nut_time[row] + COLS - 1) {
            nuts++;
            last_nut_time[row] = time;
        }
    }

    printf("%d\n", nuts);

    return 0;
}