#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000

typedef struct {
    int id;
    int score;
} Candidate;

int compare(const void *a, const void *b) {
    Candidate *ca = (Candidate *)a;
    Candidate *cb = (Candidate *)b;
    if (ca->score != cb->score) {
        return cb->score - ca->score;
    }
    return ca->id - cb->id;
}

int main() {
    int n, m;
    Candidate candidates[MAX_N];

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &candidates[i].id, &candidates[i].score);
    }

    qsort(candidates, n, sizeof(Candidate), compare);

    int cutoff_index = (m * 3) / 2 - 1;
    if (cutoff_index >= n) cutoff_index = n - 1;

    int cutoff_score = candidates[cutoff_index].score;
    int interview_count = 0;

    for (int i = 0; i < n && candidates[i].score >= cutoff_score; i++) {
        interview_count++;
    }

    printf("%d %d\n", cutoff_score, interview_count);

    for (int i = 0; i < interview_count; i++) {
        printf("%d %d\n", candidates[i].id, candidates[i].score);
    }

    return 0;
}