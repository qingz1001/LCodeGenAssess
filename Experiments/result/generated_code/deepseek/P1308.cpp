#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 11
#define MAX_ARTICLE_LEN 1000001

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    char word[MAX_WORD_LEN];
    char article[MAX_ARTICLE_LEN];
    int wordCount = 0;
    int firstPosition = -1;

    // 读取输入
    scanf("%s", word);
    getchar(); // 读取换行符
    fgets(article, MAX_ARTICLE_LEN, stdin);

    // 将输入转换为小写
    toLowerCase(word);
    toLowerCase(article);

    // 计算单词长度和文章长度
    int wordLen = strlen(word);
    int articleLen = strlen(article);

    // 遍历文章
    for (int i = 0; i <= articleLen - wordLen; i++) {
        if (i == 0 || isspace(article[i - 1])) { // 单词前必须是空格或文章开头
            if (strncmp(article + i, word, wordLen) == 0) {
                if (i + wordLen == articleLen || isspace(article[i + wordLen])) { // 单词后必须是空格或文章结尾
                    wordCount++;
                    if (firstPosition == -1) {
                        firstPosition = i;
                    }
                }
            }
        }
    }

    // 输出结果
    if (wordCount > 0) {
        printf("%d %d\n", wordCount, firstPosition);
    } else {
        printf("-1\n");
    }

    return 0;
}