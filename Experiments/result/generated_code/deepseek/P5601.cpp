#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_Q 100
#define MAX_LEN 100

typedef struct {
    char question[MAX_LEN];
    char answer[MAX_LEN];
} Question;

typedef struct {
    char question[MAX_LEN];
    char options[4][MAX_LEN];
} ExamQuestion;

Question questions[MAX_N];
ExamQuestion examQuestions[MAX_Q];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    for (int i = 0; i < n; i++) {
        scanf("%s %s", questions[i].question, questions[i].answer);
    }

    for (int i = 0; i < q; i++) {
        scanf("%s %s %s %s %s", examQuestions[i].question, 
              examQuestions[i].options[0], examQuestions[i].options[1], 
              examQuestions[i].options[2], examQuestions[i].options[3]);
    }

    for (int i = 0; i < q; i++) {
        char *correctOption = NULL;
        for (int j = 0; j < n; j++) {
            if (strcmp(examQuestions[i].question, questions[j].question) == 0) {
                correctOption = questions[j].answer;
                break;
            }
        }

        for (int k = 0; k < 4; k++) {
            if (strcmp(correctOption, examQuestions[i].options[k]) == 0) {
                printf("%c\n", 'A' + k);
                break;
            }
        }
    }

    return 0;
}