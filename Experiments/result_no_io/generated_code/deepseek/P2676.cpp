#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int N, B;
    scanf("%d %d", &N, &B);
    int *heights = (int *)malloc(N * sizeof(int));
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }
    
    qsort(heights, N, sizeof(int), compare);
    
    int sum = 0;
    int count = 0;
    
    for (int i = 0; i < N; i++) {
        sum += heights[i];
        count++;
        if (sum >= B) {
            break;
        }
    }
    
    printf("%d\n", count);
    
    free(heights);
    return 0;
}