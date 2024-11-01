#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500

typedef struct {
    int deadline;
    int penalty;
} Game;

int compare(const void *a, const void *b) {
    return ((Game*)a)->deadline - ((Game*)b)->deadline;
}

int main() {
    int m, n;
    Game games[MAX_N];
    int time[MAX_N + 1] = {0};
    int total_penalty = 0;

    scanf("%d", &m);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &games[i].deadline);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &games[i].penalty);
    }

    qsort(games, n, sizeof(Game), compare);

    for (int i = 0; i < n; i++) {
        int deadline = games[i].deadline;
        int penalty = games[i].penalty;

        int j;
        for (j = deadline; j > 0; j--) {
            if (time[j] == 0) {
                time[j] = 1;
                break;
            }
        }

        if (j == 0) {
            total_penalty += penalty;
        }
    }

    int result = m - total_penalty;
    if (result < 0) {
        result = 0;
    }

    printf("%d\n", result);

    return 0;
}