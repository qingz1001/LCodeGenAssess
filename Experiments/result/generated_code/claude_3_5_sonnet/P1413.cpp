#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2000
#define MAX_ROWS 6
#define MAX_COLS 60

typedef struct {
    int row;
    int time;
} Zombie;

int compare(const void* a, const void* b) {
    return ((Zombie*)a)->time - ((Zombie*)b)->time;
}

int main() {
    int n;
    scanf("%d", &n);

    Zombie zombies[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &zombies[i].row, &zombies[i].time);
    }

    qsort(zombies, n, sizeof(Zombie), compare);

    int nuts = 0;
    int last_kill_time[MAX_ROWS + 1] = {0};

    for (int i = 0; i < n; i++) {
        int row = zombies[i].row;
        int time = zombies[i].time;

        if (time - last_kill_time[row] >= MAX_COLS) {
            nuts++;
            last_kill_time[row] = time;
        }
    }

    printf("%d\n", nuts);

    return 0;
}