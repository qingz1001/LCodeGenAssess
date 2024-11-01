#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char word[11], article[1000001];
    int count = 0, first = -1, pos = 0, i, j;

    // 读取输入
    scanf("%s", word);
    getchar(); // 读取并丢弃行末的换行符
    fgets(article, sizeof(article), stdin);

    // 将文章和单词都转换为小写，方便比较
    for (i = 0; article[i] != '\0'; i++) {
        article[i] = tolower(article[i]);
    }
    for (i = 0; word[i] != '\0'; i++) {
        word[i] = tolower(word[i]);
    }

    // 遍历文章，查找单词
    for (i = 0; article[i] != '\0'; i++) {
        if (article[i] == word[0]) {
            // 检查是否是完全匹配的单词
            for (j = 0, pos = i; word[j] != '\0' && article[pos] != '\0'; j++, pos++) {
                if (article[pos] != word[j]) {
                    break;
                }
            }
            if (word[j] == '\0') {
                // 找到一个完全匹配的单词
                count++;
                if (first == -1) {
                    first = i;
                }
            }
        }
    }

    // 输出结果
    if (count > 0) {
        printf("%d %d\n", count, first);
    } else {
        printf("%d\n", -1);
    }

    return 0;
}