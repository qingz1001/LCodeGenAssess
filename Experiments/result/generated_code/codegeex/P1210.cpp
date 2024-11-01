#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 20000

int main() {
    char input[MAX_LEN + 1];
    char clean[MAX_LEN + 1];
    char longest_palindrome[MAX_LEN + 1];
    int len, longest_len = 0;

    // 读取输入
    char ch = getchar();
    int i = 0;
    while (ch != EOF) {
        if (i < MAX_LEN) {
            input[i++] = ch;
        }
        ch = getchar();
    }
    input[i] = '\0';

    // 清洗输入，保留字母和空格
    int j = 0;
    for (int k = 0; k < i; k++) {
        if (isalpha(input[k]) || input[k] == ' ') {
            clean[j++] = tolower(input[k]);
        }
    }
    clean[j] = '\0';
    len = j;

    // 寻找最长回文
    for (int start = 0; start < len; start++) {
        int l = start, r = start;
        // 找到连续相同的字符
        while (r < len - 1 && clean[r] == clean[r + 1]) {
            r++;
        }
        // 更新start到连续相同字符的末尾
        start = r;
        // 尝试扩展回文
        while (l > 0 && r < len - 1 && clean[l - 1] == clean[r + 1]) {
            l--;
            r++;
        }
        // 检查是否是最长回文
        if (r - l + 1 > longest_len) {
            longest_len = r - l + 1;
            strncpy(longest_palindrome, &input[l], longest_len);
            longest_palindrome[longest_len] = '\0';
        }
    }

    // 输出结果
    printf("%d\n", longest_len);
    for (int i = 0; i < strlen(input); i++) {
        if (strstr(longest_palindrome, &input[i])) {
            printf("%c", input[i]);
        }
    }
    printf("\n");

    return 0;
}