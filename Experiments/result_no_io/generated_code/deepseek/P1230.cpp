#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int deadline;
    int penalty;
} Game;

int compare(const void *a, const void *b) {
    Game *gameA = (Game *)a;
    Game *gameB = (Game *)b;
    if (gameA->penalty == gameB->penalty) {
        return gameA->deadline - gameB->deadline;
    }
    return gameB->penalty - gameA->penalty;
}

int main() {
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);

    Game games[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &games[i].deadline);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &games[i].penalty);
    }

    qsort(games, n, sizeof(Game), compare);

    int timeSlots[n];
    for (int i = 0; i < n; i++) {
        timeSlots[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int deadline = games[i].deadline;
        while (deadline > 0 && timeSlots[deadline - 1] != 0) {
            deadline--;
        }
        if (deadline > 0) {
            timeSlots[deadline - 1] = 1;
        } else {
            m -= games[i].penalty;
        }
    }

    printf("%d\n", m);

    return 0;
}