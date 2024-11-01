#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500

typedef struct {
    int deadline;
    int penalty;
} Game;

int compare(const void *a, const void *b) {
    Game *gameA = (Game *)a;
    Game *gameB = (Game *)b;
    if (gameA->deadline != gameB->deadline) {
        return gameA->deadline - gameB->deadline;
    }
    return gameB->penalty - gameA->penalty;
}

int main() {
    int m, n;
    Game games[MAX_N];
    int timeline[MAX_N + 1] = {0};
    
    scanf("%d", &m);
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &games[i].deadline);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &games[i].penalty);
    }
    
    qsort(games, n, sizeof(Game), compare);
    
    int total_penalty = 0;
    for (int i = 0; i < n; i++) {
        int deadline = games[i].deadline;
        while (deadline > 0 && timeline[deadline]) {
            deadline--;
        }
        if (deadline > 0) {
            timeline[deadline] = 1;
        } else {
            total_penalty += games[i].penalty;
        }
    }
    
    int result = m - total_penalty;
    printf("%d\n", result);
    
    return 0;
}