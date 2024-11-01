#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int deadline;
    int penalty;
} Game;

int compare(const void *a, const void *b) {
    Game *gameA = (Game *)a;
    Game *gameB = (Game *)b;
    if (gameA->penalty != gameB->penalty) {
        return gameB->penalty - gameA->penalty; // Sort by penalty in descending order
    } else {
        return gameA->deadline - gameB->deadline; // If penalties are equal, sort by deadline in ascending order
    }
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

    int schedule[n];
    for (int i = 0; i < n; i++) {
        schedule[i] = -1; // Initialize schedule slots to -1 (indicating empty)
    }

    for (int i = 0; i < n; i++) {
        for (int j = games[i].deadline - 1; j >= 0; j--) {
            if (schedule[j] == -1) {
                schedule[j] = i;
                break;
            }
        }
    }

    int totalPenalty = 0;
    for (int i = 0; i < n; i++) {
        if (schedule[i] == -1) {
            totalPenalty += games[i].penalty;
        }
    }

    printf("%d\n", m - totalPenalty);

    return 0;
}