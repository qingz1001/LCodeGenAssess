#include <stdio.h>
#include <string.h>

int main() {
    char s[101];
    scanf("%[^\n]", s); // 读取一行输入直到换行符
    int n = strlen(s); // 获取字符串长度

    for (int i = 0; i < n; i++) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
            printf("%c", s[i]); // 如果是元音字母，直接输出
            i += 2; // 跳过后面跟着的 'p' 和重复的元音字母
        } else {
            printf("%c", s[i]); // 如果不是元音字母，直接输出
        }
    }
    printf("\n"); // 输出解密后的字符串
    return 0;
}