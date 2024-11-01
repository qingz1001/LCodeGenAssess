#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long *scores = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &scores[i]);
    }

    // Sort the scores in ascending order
    qsort(scores, n, sizeof(long long), compare);

    long long total = 0;
    for (int i = 1; i < n - 1; i++) {
        total += scores[i];
    }

    long long max_final_score = total;

    // Try to increase one score and see if it can improve the final score
    for (int i = 0; i < n && m > 0; i++) {
        long long new_total = total - scores[i] + scores[i] + 1;
        if (new_total > max_final_score) {
            max_final_score = new_total;
        }
        m--;
    }

    printf("%lld\n", max_final_score);

    free(scores);
    return 0;
}

int compare(const void *a, const void *b) {
    return (*(long long *)a - *(long long *)b);
}