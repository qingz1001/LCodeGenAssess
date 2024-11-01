#include <stdio.h>
#include <string.h>

int main() {
    char s[101];
    scanf("%[^\n]", s); // 读取一整行字符串，直到遇到换行符
    int len = strlen(s);
    int i = 0;

    while (i < len) {
        if (s[i] == 'p') {
            if (s[i+1] == 'e' || s[i+1] == 'a' || s[i+1] == 'i' || s[i+1] == 'o' || s[i+1] == 'u') {
                printf("%c", s[i+1]); // 输出元音字母
                i += 2; // 跳过 'p' 和元音字母
            } else {
                printf("%c", s[i]); // 输出其他字符
                i++;
            }
        } else {
            printf("%c", s[i]); // 输出非 'p' 字符
            i++;
        }
    }

    return 0;
}