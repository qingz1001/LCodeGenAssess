#include <stdio.h>

int main() {
    int n, dist;
    scanf("%d %d", &n, &dist);
    
    int positions[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }
    
    // 排序灯的位置
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (positions[i] > positions[j]) {
                int temp = positions[i];
                positions[i] = positions[j];
                positions[j] = temp;
            }
        }
    }
    
    int maxDeletions = 0;
    int currentDeletions = 0;
    
    for (int i = 1; i < n - 1; i++) {
        if (positions[i + 1] - positions[i - 1] <= dist) {
            currentDeletions++;
        } else {
            if (currentDeletions > maxDeletions) {
                maxDeletions = currentDeletions;
            }
            currentDeletions = 0;
        }
    }
    
    if (currentDeletions > maxDeletions) {
        maxDeletions = currentDeletions;
    }
    
    printf("%d\n", maxDeletions);
    
    return 0;
}