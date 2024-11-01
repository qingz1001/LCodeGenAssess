#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

int main() {
    char keywords[MAX_LEN], question[MAX_LEN];
    int key_len, que_len;
    int i, j, k;
    int found;

    // 输入关键词和题目
    fgets(keywords, MAX_LEN, stdin);
    fgets(question, MAX_LEN, stdin);

    // 去掉换行符
    key_len = strlen(keywords);
    if (keywords[key_len - 1] == '\n') {
        keywords[key_len - 1] = '\0';
        key_len--;
    }

    que_len = strlen(question);
    if (question[que_len - 1] == '\n') {
        question[que_len - 1] = '\0';
        que_len--;
    }

    // 处理题目中的词语
    for (i = 0, j = 0; i < que_len; i++) {
        if (question[i] == ' ') {
            // 如果是空格，跳过
            continue;
        } else if (question[i] == '<' && question[i + 1] == 'b' && question[i + 2] == '>') {
            // 如果是闭合标签，跳过
            i += 2;
            continue;
        } else {
            // 找到关键词
            found = 0;
            for (k = 0; k < key_len; k++) {
                if (question[i + k] != keywords[k] && keywords[k] != ' ') {
                    break;
                }
                if (k == key_len - 1 && question[i + k + 1] == ' ' || question[i + k + 1] == '\0') {
                    found = 1;
                    break;
                }
            }
            if (found) {
                // 如果找到关键词，添加标记
                for (k = 0; k < key_len; k++) {
                    printf("%c", question[i + k]);
                }
                printf("</b>");
                i += k - 1;
            } else {
                // 如果没有找到关键词，直接输出
                printf("%c", question[i]);
            }
        }
    }

    return 0;
}