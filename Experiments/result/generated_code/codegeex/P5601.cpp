#include <stdio.h>
#include <string.h>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    char questions[101][101];
    char answers[101][101];
    char question[101];
    char options[4][101];
    char correct_option;

    // 读取题库信息
    for (int i = 0; i < n; i++) {
        scanf("%s %s", questions[i], answers[i]);
    }

    // 处理模拟考试题目
    for (int i = 0; i < q; i++) {
        scanf("%s", question);
        for (int j = 0; j < 4; j++) {
            scanf("%s", options[j]);
        }

        // 查找题目对应的答案
        for (int j = 0; j < n; j++) {
            if (strcmp(question, questions[j]) == 0) {
                correct_option = 'A' + strchr(options, answers[j]) - options;
                break;
            }
        }

        printf("%c\n", correct_option);
    }

    return 0;
}