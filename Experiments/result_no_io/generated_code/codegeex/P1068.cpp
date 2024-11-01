#include <stdio.h>

typedef struct {
    int id;
    int score;
} Candidate;

int cmp(const void *a, const void *b) {
    Candidate *candidateA = (Candidate *)a;
    Candidate *candidateB = (Candidate *)b;
    if (candidateA->score != candidateB->score) {
        return candidateB->score - candidateA->score;
    } else {
        return candidateA->id - candidateB->id;
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    Candidate candidates[n];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &candidates[i].id, &candidates[i].score);
    }

    qsort(candidates, n, sizeof(Candidate), cmp);

    int thresholdIndex = (int)(m * 1.5);
    int threshold = candidates[thresholdIndex - 1].score;

    int actualCount = 0;
    for (int i = 0; i < n; i++) {
        if (candidates[i].score >= threshold) {
            actualCount++;
        } else {
            break;
        }
    }

    printf("%d %d\n", threshold, actualCount);
    for (int i = 0; i < actualCount; i++) {
        printf("%d %d\n", candidates[i].id, candidates[i].score);
    }

    return 0;
}