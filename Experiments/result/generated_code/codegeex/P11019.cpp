#include <stdio.h>
#include <string.h>

int main() {
    char str[105];
    scanf("%s", str);
    int len = strlen(str);

    // 输出第一个字符的拼音缩写
    printf("/%c", tolower(str[1]));

    // 遍历字符串，输出每个音节的第一个字母的拼音缩写
    for (int i = 2; i < len - 2; i++) {
        if (str[i] == '[') {
            printf("%c", tolower(str[i + 1]));
        }
    }

    printf("\n");
    return 0;
}