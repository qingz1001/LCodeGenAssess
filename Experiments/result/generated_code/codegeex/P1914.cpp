#include <stdio.h>

int main() {
    int n;
    char str[51];

    // 读取输入
    scanf("%d", &n);
    scanf("%s", str);

    int len = 0;
    while (str[len] != '\0') {
        len++;
    }

    // 对每个字符进行移位操作
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = (str[i] - 'a' + n) % 26 + 'a';
        }
    }

    // 输出结果
    printf("%s\n", str);

    return 0;
}