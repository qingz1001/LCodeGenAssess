#include <stdio.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 60
#define MAX_TIME 100000

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

    Zombie zombies[2000];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &zombies[i].row, &zombies[i].time);
    }

    qsort(zombies, n, sizeof(Zombie), compare);

    int last_time[ROWS + 1] = {0};
    int nut_count = 0;

    for (int i = 0; i < n; i++) {
        int row = zombies[i].row;
        int time = zombies[i].time;

        if (time > last_time[row]) {
            last_time[row] = time + COLS - 1;
            nut_count++;
        }
    }

    printf("%d\n", nut_count);

    return 0;
}