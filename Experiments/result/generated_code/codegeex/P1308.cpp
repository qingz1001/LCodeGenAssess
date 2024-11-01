#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char target[11], article[1000001];
    scanf("%s", target);
    scanf("%s", article);

    int targetLen = strlen(target);
    int articleLen = strlen(article);
    int count = 0;
    int firstPos = -1;

    // 将目标单词和文章都转换为小写
    for (int i = 0; i < targetLen; i++) {
        target[i] = tolower(target[i]);
    }
    for (int i = 0; i < articleLen; i++) {
        article[i] = tolower(article[i]);
    }

    // 遍历文章，查找目标单词
    for (int i = 0; i <= articleLen - targetLen; i++) {
        int match = 1;
        for (int j = 0; j < targetLen; j++) {
            if (article[i + j] != target[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            count++;
            if (firstPos == -1) {
                firstPos = i;
            }
        }
    }

    if (count > 0) {
        printf("%d %d\n", count, firstPos);
    } else {
        printf("-1\n");
    }

    return 0;
}