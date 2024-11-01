#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int score;
} Candidate;

int compare(const void *a, const void *b) {
    Candidate *ca = (Candidate *)a;
    Candidate *cb = (Candidate *)b;
    if (ca->score != cb->score) {
        return cb->score - ca->score;
    } else {
        return ca->id - cb->id;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Candidate candidates[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &candidates[i].id, &candidates[i].score);
    }

    qsort(candidates, n, sizeof(Candidate), compare);

    int cutoff = (int)(m * 1.5);
    int score_cutoff = candidates[cutoff - 1].score;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (candidates[i].score >= score_cutoff) {
            count++;
        } else {
            break;
        }
    }

    printf("%d %d\n", score_cutoff, count);
    for (int i = 0; i < count; i++) {
        printf("%d %d\n", candidates[i].id, candidates[i].score);
    }

    return 0;
}