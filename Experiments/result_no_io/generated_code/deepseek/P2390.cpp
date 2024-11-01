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
    int current_position = 0;
    
    for (int i = 0; i < n; i++) {
        int distance = abs(landmarks[i] - current_position);
        if (current_time + distance <= t) {
            current_time += distance;
            current_position = landmarks[i];
            max_landmarks++;
        } else {
            break;
        }
    }
    
    printf("%d\n", max_landmarks);
    
    free(landmarks);
    return 0;
}