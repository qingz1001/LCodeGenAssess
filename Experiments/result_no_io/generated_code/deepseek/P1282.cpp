#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int upper_sum = 0, lower_sum = 0;
    int domino[n][2];
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &domino[i][0], &domino[i][1]);
        upper_sum += domino[i][0];
        lower_sum += domino[i][1];
    }
    
    int initial_diff = abs(upper_sum - lower_sum);
    int min_rotations = 0;
    int min_diff = initial_diff;
    
    for (int i = 0; i < n; i++) {
        int new_upper_sum = upper_sum - domino[i][0] + domino[i][1];
        int new_lower_sum = lower_sum - domino[i][1] + domino[i][0];
        int new_diff = abs(new_upper_sum - new_lower_sum);
        
        if (new_diff < min_diff) {
            min_diff = new_diff;
            min_rotations = 1;
        } else if (new_diff == min_diff) {
            min_rotations = (min_rotations == 0) ? 1 : min_rotations;
        }
    }
    
    printf("%d\n", min_rotations);
    
    return 0;
}