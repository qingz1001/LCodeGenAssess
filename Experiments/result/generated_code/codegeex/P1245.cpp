#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20
#define MAX_PASSWORD_LENGTH 100

int main() {
    int N;
    char password[MAX_PASSWORD_LENGTH + 1];
    char words[MAX_WORDS][MAX_WORD_LENGTH + 1];
    char phone[10][4] = {
        {'\0'}, {'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'},
        {'j', 'k', 'l'}, {'m', 'n'}, {'o', 'p', 'q'}, {'r', 's', 't'},
        {'u', 'v', 'w'}, {'x', 'y', 'z'}
    };

    // 读取单词数量和密码
    scanf("%d", &N);
    scanf("%s", password);

    // 读取单词表
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i]);
    }

    // 尝试将密码翻译成单词
    for (int i = 0; i < N; i++) {
        int word_length = strlen(words[i]);
        if (word_length > strlen(password)) {
            continue;
        }
        int j;
        for (j = 0; j < word_length; j++) {
            int digit = password[j] - '0';
            char *letter = strchr(phone[digit], words[i][j]);
            if (letter == NULL) {
                break;
            }
        }
        if (j == word_length) {
            printf("%s ", words[i]);
        }
    }

    // 检查是否找到解决方案
    if (strlen(password) > 0) {
        printf("No Solutions!\n");
    }

    return 0;
}