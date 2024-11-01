#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    int *scores = (int *)malloc(N * sizeof(int));
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &scores[i]);
    }
    
    // Sort the scores array
    qsort(scores, N, sizeof(int), (int (*)(const void *, const void *))strcmp);
    
    int max_average = 0;
    int *max_Ks = (int *)malloc(N * sizeof(int));
    int max_count = 0;
    
    for (int k = 1; k < N - 1; k++) {
        int sum = 0;
        for (int i = k; i < N - 1; i++) {
            sum += scores[i];
        }
        int average = (sum + scores[N - 1]) / (N - k - 1);
        
        if (average > max_average) {
            max_average = average;
            max_count = 0;
            max_Ks[max_count++] = k;
        } else if (average == max_average) {
            max_Ks[max_count++] = k;
        }
    }
    
    for (int i = 0; i < max_count; i++) {
        printf("%d\n", max_Ks[i]);
    }
    
    free(scores);
    free(max_Ks);
    
    return 0;
}