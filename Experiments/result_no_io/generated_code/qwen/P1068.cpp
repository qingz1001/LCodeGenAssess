#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000

typedef struct {
    int id;
    int score;
} Participant;

int compare(const void *a, const void *b) {
    Participant *p1 = (Participant *)a;
    Participant *p2 = (Participant *)b;
    if (p1->score != p2->score) {
        return p2->score - p1->score;
    }
    return p1->id - p2->id;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Participant participants[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &participants[i].id, &participants[i].score);
    }

    qsort(participants, n, sizeof(Participant), compare);

    int cutoff = participants[(int)(m * 1.5) - 1].score;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (participants[i].score >= cutoff) {
            printf("%d %d\n", participants[i].id, participants[i].score);
            count++;
        } else {
            break;
        }
    }
    printf("%d %d\n", cutoff, count);

    return 0;
}