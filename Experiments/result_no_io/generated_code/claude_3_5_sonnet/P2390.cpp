#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 50000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int t, n;
    scanf("%d %d", &t, &n);

    int landmarks[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &landmarks[i]);
    }

    qsort(landmarks, n, sizeof(int), compare);

    int left = 0, right = 0, max_visited = 0;
    int current_time = 0, current_position = 0;

    while (right < n) {
        int time_to_right = abs(landmarks[right] - current_position);
        
        if (current_time + time_to_right <= t) {
            current_time += time_to_right;
            current_position = landmarks[right];
            right++;
            max_visited = right - left;
        } else {
            if (left == right) {
                right++;
            } else {
                int time_from_left = abs(landmarks[left] - current_position);
                current_time -= time_from_left;
                current_position = landmarks[left];
                left++;
            }
        }
    }

    printf("%d\n", max_visited);

    return 0;
}