#include <stdio.h>
#include <string.h>

int main() {
    char s[105];
    scanf("%s", s);

    // 初始化结果字符串
    char result[105] = "/";

    // 遍历字符串，提取每个拼音的首字母
    for (int i = 1; i < strlen(s) - 2; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            result[i + 1] = s[i] + 32; // 将大写字母转换为小写字母
        }
    }

    // 输出结果
    printf("%s\n", result);

    return 0;
}