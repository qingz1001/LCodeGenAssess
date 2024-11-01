#include <stdio.h>
#include <string.h>

void process_scores(int score_limit) {
    char line[26];
    int w_score = 0, l_score = 0;

    while (1) {
        scanf("%s", line);
        for (int i = 0; i < strlen(line); i++) {
            if (line[i] == 'E') {
                printf("%d:%d\n", w_score, l_score);
                return;
            }
            if (line[i] == 'W') w_score++;
            if (line[i] == 'L') l_score++;

            if ((w_score >= score_limit || l_score >= score_limit) && abs(w_score - l_score) >= 2) {
                printf("%d:%d\n", w_score, l_score);
                w_score = 0;
                l_score = 0;
            }
        }
    }
}

int main() {
    printf("11分制结果:\n");
    process_scores(11);
    printf("\n21分制结果:\n");
    process_scores(21);
    return 0;
}