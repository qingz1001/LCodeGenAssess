#include <stdio.h>

int main() {
    int scores[5] = {0, 0, 0, 0, 0};
    int max_score = 0;
    int max_index = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            int rating;
            scanf("%d", &rating);
            scores[i] += rating;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (scores[i] > max_score) {
            max_score = scores[i];
            max_index = i + 1;
        }
    }

    printf("%d %d\n", max_index, max_score);

    return 0;
}