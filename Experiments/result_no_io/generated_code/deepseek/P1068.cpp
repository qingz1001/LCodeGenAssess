#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int score;
} Player;

int compare(const void *a, const void *b) {
    Player *p1 = (Player *)a;
    Player *p2 = (Player *)b;
    if (p1->score != p2->score) {
        return p2->score - p1->score;
    } else {
        return p1->id - p2->id;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Player players[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &players[i].id, &players[i].score);
    }

    qsort(players, n, sizeof(Player), compare);

    int cutoff = (int)(m * 1.5);
    int score_line = players[cutoff - 1].score;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (players[i].score >= score_line) {
            count++;
        }
    }

    printf("%d %d\n", score_line, count);
    for (int i = 0; i < count; i++) {
        printf("%d %d\n", players[i].id, players[i].score);
    }

    return 0;
}