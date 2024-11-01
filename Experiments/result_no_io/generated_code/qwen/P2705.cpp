#include <stdio.h>
#include <stdlib.h>

int main() {
    int R, B, C, D, E;
    scanf("%d %d %d %d %d", &R, &B, &C, &D, &E);

    int max_score = 0;

    for (int red_boxes_used = 0; red_boxes_used <= R && red_boxes_used <= B; red_boxes_used++) {
        int blue_boxes_used = R + B - red_boxes_used;
        int score = (red_boxes_used * C) + (blue_boxes_used * D);
        if (red_boxes_used > blue_boxes_used) {
            score += (red_boxes_used - blue_boxes_used) * E;
        } else {
            score += (blue_boxes_used - red_boxes_used) * E;
        }
        if (score > max_score) {
            max_score = score;
        }
    }

    printf("%d\n", max_score);

    return 0;
}