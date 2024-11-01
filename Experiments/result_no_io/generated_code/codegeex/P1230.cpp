#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int deadline;
    int penalty;
} Game;

int compare(const void *a, const void *b) {
    Game *gameA = (Game *)a;
    Game *gameB = (Game *)b;
    return gameA->deadline - gameB->deadline;
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

    int totalPenalty = 0;
    for (int i = 0; i < n; i++) {
        if (games[i].deadline <= i + 1) {
            totalPenalty += games[i].penalty;
        }
    }

    printf("%d\n", m - totalPenalty);

    return 0;
}