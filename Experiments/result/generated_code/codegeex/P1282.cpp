#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int domino[1005][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &domino[i][0], &domino[i][1]);
    }
    
    int diff = 0;
    for (int i = 0; i < n; i++) {
        diff += domino[i][0] - domino[i][1];
    }
    
    int min_diff = diff;
    int min_rotations = 0;
    
    for (int i = 0; i < n; i++) {
        int new_diff = diff - 2 * (domino[i][0] - domino[i][1]);
        if (new_diff < min_diff) {
            min_diff = new_diff;
            min_rotations = 1;
        } else if (new_diff == min_diff) {
            min_rotations++;
        }
    }
    
    printf("%d\n", min_rotations);
    return 0;
}