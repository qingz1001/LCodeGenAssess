#include <stdio.h>
#include <string.h>

#define MAX_SIZE 101

typedef struct {
    char question[MAX_SIZE];
    char answer[MAX_SIZE];
} Question;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    Question questions[MAX_SIZE];
    for (int i = 0; i < n; i++) {
        scanf("%s %s", questions[i].question, questions[i].answer);
    }

    for (int i = 0; i < q; i++) {
        char question[MAX_SIZE];
        char options[4][MAX_SIZE];
        scanf("%s %s %s %s %s", question, options[0], options[1], options[2], options[3]);

        for (int j = 0; j < n; j++) {
            if (strcmp(questions[j].question, question) == 0) {
                for (int k = 0; k < 4; k++) {
                    if (strcmp(questions[j].answer, options[k]) == 0) {
                        printf("%c\n", 'A' + k);
                        break;
                    }
                }
                break;
            }
        }
    }

    return 0;
}