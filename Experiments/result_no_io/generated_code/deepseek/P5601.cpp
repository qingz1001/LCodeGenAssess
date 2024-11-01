#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_Q 100
#define MAX_S 100

typedef struct {
    char question[MAX_S];
    char answer[MAX_S];
} Question;

typedef struct {
    char question[MAX_S];
    char options[4][MAX_S];
} ExamQuestion;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    Question questions[MAX_N];
    ExamQuestion examQuestions[MAX_Q];

    for (int i = 0; i < n; i++) {
        scanf("%s %s", questions[i].question, questions[i].answer);
    }

    for (int i = 0; i < q; i++) {
        scanf("%s %s %s %s %s", examQuestions[i].question, 
              examQuestions[i].options[0], examQuestions[i].options[1], 
              examQuestions[i].options[2], examQuestions[i].options[3]);
    }

    for (int i = 0; i < q; i++) {
        char *currentQuestion = examQuestions[i].question;
        char *correctAnswer = NULL;

        for (int j = 0; j < n; j++) {
            if (strcmp(currentQuestion, questions[j].question) == 0) {
                correctAnswer = questions[j].answer;
                break;
            }
        }

        if (correctAnswer != NULL) {
            for (int k = 0; k < 4; k++) {
                if (strcmp(correctAnswer, examQuestions[i].options[k]) == 0) {
                    printf("%c\n", 'A' + k);
                    break;
                }
            }
        }
    }

    return 0;
}