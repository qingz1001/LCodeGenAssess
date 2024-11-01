#include <stdio.h>

int main() {
    char s[9];
    int count = 0;

    // 读取输入的01字符串
    scanf("%s", s);

    // 遍历字符串，统计字符 '1' 的个数
    for (int i = 0; i < 8; i++) {
        if (s[i] == '1') {
            count++;
        }
    }

    // 输出结果
    printf("%d\n", count);

    return 0;
}