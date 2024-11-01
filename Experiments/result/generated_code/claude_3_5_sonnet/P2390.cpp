#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 50000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int t, n;
    int landmarks[MAX_N];
    
    scanf("%d %d", &t, &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &landmarks[i]);
    }
    
    qsort(landmarks, n, sizeof(int), compare);
    
    int left = 0, right = 0;
    int max_visited = 0;
    int current_time = 0;
    
    while (right < n) {
        while (right < n && current_time + abs(landmarks[right] - (right > 0 ? landmarks[right-1] : 0)) <= t) {
            current_time += abs(landmarks[right] - (right > 0 ? landmarks[right-1] : 0));
            right++;
        }
        
        int visited = right - left;
        if (visited > max_visited) {
            max_visited = visited;
        }
        
        if (left < right) {
            current_time -= abs(landmarks[left+1] - landmarks[left]);
            left++;
        } else {
            right++;
        }
    }
    
    printf("%d\n", max_visited);
    
    return 0;
}