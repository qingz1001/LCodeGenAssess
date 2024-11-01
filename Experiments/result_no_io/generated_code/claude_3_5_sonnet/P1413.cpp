#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2000
#define MAX_ROWS 6
#define MAX_TIME 100000

typedef struct {
    int row;
    int time;
} Zombie;

int compare(const void *a, const void *b) {
    return ((Zombie *)a)->time - ((Zombie *)b)->time;
}

int main() {
    int n;
    scanf("%d", &n);

    Zombie zombies[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &zombies[i].row, &zombies[i].time);
    }

    qsort(zombies, n, sizeof(Zombie), compare);

    int last_kill_time[MAX_ROWS + 1] = {0};
    int nuts_count = 0;

    for (int i = 0; i < n; i++) {
        int row = zombies[i].row;
        int time = zombies[i].time;

        if (time >= last_kill_time[row]) {
            nuts_count++;
            last_kill_time[row] = time + 60;
        }
    }

    printf("%d\n", nuts_count);

    return 0;
}