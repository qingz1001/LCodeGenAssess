#include <stdio.h>
#include <string.h>

int main() {
    char input[2510][30];
    int num = 0;
    while (1) {
        scanf("%s", input[num]);
        if (input[num][0] == 'E') {
            break;
        }
        num++;
    }

    // 11分制
    int score_11W = 0, score_11L = 0;
    int current_set_11 = 1;
    printf("%d:%d\n", score_11W, score_11L);
    for (int i = 0; i < num; i++) {
        if (input[i][0] == 'W') {
            score_11W++;
        } else {
            score_11L++;
        }
        if ((score_11W >= 11 || score_11L >= 11) && (score_11W - score_11L >= 2 || score_11L - score_11W >= 2)) {
            current_set_11++;
            printf("%d:%d\n", score_11W, score_11L);
            score_11W = 0;
            score_11L = 0;
        }
    }
    printf("%d:%d\n\n", score_11W, score_11L);

    // 21分制
    int score_21W = 0, score_21L = 0;
    int current_set_21 = 1;
    printf("%d:%d\n", score_21W, score_21L);
    for (int i = 0; i < num; i++) {
        if (input[i][0] == 'W') {
            score_21W++;
        } else {
            score_21L++;
        }
        if ((score_21W >= 21 || score_21L >= 21) && (score_21W - score_21L >= 2 || score_21L - score_21W >= 2)) {
            current_set_21++;
            printf("%d:%d\n", score_21W, score_21L);
            score_21W = 0;
            score_21L = 0;
        }
    }
    printf("%d:%d\n", score_21W, score_21L);

    return 0;
}