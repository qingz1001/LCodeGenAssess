#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000000

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    char word[11], article[MAX_LEN + 1];
    char temp[MAX_LEN + 1];
    int count = 0, firstPos = -1;

    scanf("%s", word);
    getchar(); // 消耗换行符
    fgets(article, MAX_LEN, stdin);

    // 去除可能的换行符
    int len = strlen(article);
    if (article[len - 1] == '\n') {
        article[len - 1] = '\0';
    }

    toLowerCase(word);
    strcpy(temp, article);
    toLowerCase(temp);

    char *ptr = temp;
    int pos = 0;

    while ((ptr = strstr(ptr, word)) != NULL) {
        // 检查是否为独立单词
        int start = (ptr == temp) || !isalpha(*(ptr - 1));
        int end = !isalpha(*(ptr + strlen(word)));

        if (start && end) {
            count++;
            if (firstPos == -1) {
                firstPos = ptr - temp;
            }
        }
        ptr += strlen(word);
    }

    if (count > 0) {
        printf("%d %d\n", count, firstPos);
    } else {
        printf("-1\n");
    }

    return 0;
}