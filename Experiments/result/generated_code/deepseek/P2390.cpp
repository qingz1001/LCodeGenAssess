#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int t, n;
    scanf("%d %d", &t, &n);
    
    int *landmarks = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &landmarks[i]);
    }
    
    qsort(landmarks, n, sizeof(int), compare);
    
    int max_landmarks = 0;
    int current_time = 0;
    
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            current_time = abs(landmarks[i]);
        } else {
            current_time += abs(landmarks[i] - landmarks[i - 1]);
        }
        
        if (current_time <= t) {
            max_landmarks++;
        } else {
            break;
        }
    }
    
    printf("%d\n", max_landmarks);
    
    free(landmarks);
    return 0;
}