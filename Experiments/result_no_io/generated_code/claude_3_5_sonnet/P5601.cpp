#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_Q 100
#define MAX_S 101 // 多一个字符用于存储字符串结束符 '\0'

char questions[MAX_N][MAX_S];
char answers[MAX_N][MAX_S];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    // 读取题目和答案
    for (int i = 0; i < n; i++) {
        scanf("%s %s", questions[i], answers[i]);
    }

    // 处理模拟考试题目
    for (int i = 0; i < q; i++) {
        char question[MAX_S];
        char options[4][MAX_S];
        scanf("%s %s %s %s %s", question, options[0], options[1], options[2], options[3]);

        // 查找匹配的题目
        for (int j = 0; j < n; j++) {
            if (strcmp(question, questions[j]) == 0) {
                // 找到匹配的题目，检查选项
                for (int k = 0; k < 4; k++) {
                    if (strcmp(options[k], answers[j]) == 0) {
                        printf("%c", 'A' + k);
                        break;
                    }
                }
                break;
            }
        }
    }

    return 0;
}