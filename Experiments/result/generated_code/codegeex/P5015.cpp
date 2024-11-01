#include <stdio.h>
#include <ctype.h>

int main() {
    char c;
    int count = 0;

    // 读取输入直到遇到换行符
    while ((c = getchar()) != '\n') {
        // 如果字符不是空格，则计数加一
        if (!isspace(c)) {
            count++;
        }
    }

    // 输出计数结果
    printf("%d\n", count);

    return 0;
}