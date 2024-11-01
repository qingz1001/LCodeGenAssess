#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

long long minUnsatisfaction(int m, int n, int *scores, int *estimates) {
    qsort(scores, m, sizeof(int), compare);
    
    long long total_unsatisfaction = 0;
    for (int i = 0; i < n; i++) {
        int index = 0;
        while (index < m && scores[index] < estimates[i]) {
            index++;
        }
        if (index == m) {
            total_unsatisfaction += abs(estimates[i] - scores[m-1]);
        } else if (index == 0) {
            total_unsatisfaction += abs(estimates[i] - scores[0]);
        } else {
            total_unsatisfaction += abs(estimates[i] - scores[index]);
            if (index > 0 && abs(estimates[i] - scores[index-1]) < abs(estimates[i] - scores[index])) {
                total_unsatisfaction -= abs(estimates[i] - scores[index]);
                total_unsatisfaction += abs(estimates[i] - scores[index-1]);
                index--;
            }
        }
    }
    
    return total_unsatisfaction;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    int *scores = (int *)malloc(m * sizeof(int));
    int *estimates = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &scores[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &estimates[i]);
    }
    
    printf("%lld\n", minUnsatisfaction(m, n, scores, estimates));
    
    free(scores);
    free(estimates);
    
    return 0;
}