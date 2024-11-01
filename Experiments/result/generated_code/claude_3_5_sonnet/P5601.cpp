#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_Q 100
#define MAX_S 101

char questions[MAX_N][MAX_S];
char answers[MAX_N][MAX_S];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    for (int i = 0; i < n; i++) {
        scanf("%s %s", questions[i], answers[i]);
    }

    for (int i = 0; i < q; i++) {
        char question[MAX_S], options[4][MAX_S];
        scanf("%s %s %s %s %s", question, options[0], options[1], options[2], options[3]);

        int question_index = -1;
        for (int j = 0; j < n; j++) {
            if (strcmp(questions[j], question) == 0) {
                question_index = j;
                break;
            }
        }

        char result = 'A';
        for (int j = 0; j < 4; j++) {
            if (strcmp(options[j], answers[question_index]) == 0) {
                result = 'A' + j;
                break;
            }
        }

        printf("%c\n", result);
    }

    return 0;
}