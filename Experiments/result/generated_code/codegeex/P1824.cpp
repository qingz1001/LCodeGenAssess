#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N, C;
    scanf("%d %d", &N, &C);
    
    int *positions = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &positions[i]);
    }
    
    qsort(positions, N, sizeof(int), compare);
    
    int low = 1;
    int high = positions[N-1] - positions[0];
    int result = 0;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        int count = 1;
        int last_position = positions[0];
        
        for (int i = 1; i < N; i++) {
            if (positions[i] - last_position >= mid) {
                count++;
                last_position = positions[i];
            }
        }
        
        if (count >= C) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    printf("%d\n", result);
    
    free(positions);
    return 0;
}