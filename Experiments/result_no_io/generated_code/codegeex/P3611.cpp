#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, T_max;
    scanf("%d %d", &N, &T_max);
    
    int *durations = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &durations[i]);
    }
    
    int left = 1, right = N, mid;
    while (left < right) {
        mid = (left + right) / 2;
        
        int current_time = 0;
        for (int i = 0; i < mid; i++) {
            current_time += durations[i];
        }
        
        for (int i = mid; i < N; i++) {
            if (current_time + durations[i] > T_max) {
                right = mid;
                break;
            }
            current_time += durations[i] - durations[i - mid];
        }
        
        if (current_time <= T_max) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    printf("%d\n", left);
    free(durations);
    return 0;
}