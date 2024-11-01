#include <stdio.h>

int main() {
    int scores[5][4];
    int total_scores[5] = {0};
    
    // Read scores from input
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &scores[i][j]);
            total_scores[i] += scores[i][j];
        }
    }
    
    // Find the highest score and its index
    int max_score = total_scores[0];
    int max_index = 0;
    for (int i = 1; i < 5; i++) {
        if (total_scores[i] > max_score) {
            max_score = total_scores[i];
            max_index = i;
        }
    }
    
    // Output the result
    printf("%d %d\n", max_index + 1, max_score);
    
    return 0;
}