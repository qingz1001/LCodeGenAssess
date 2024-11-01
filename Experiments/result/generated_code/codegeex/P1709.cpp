#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 5000000

char str[MAX_LEN];
int n;

int main() {
    // 读取输入
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf(" %c", &str[i]); // 注意前面的空格，用于跳过换行符
    }

    // 计算并输出结果
    int min_index = MAX_LEN;
    char min_char = 'z' + 1; // 初始化为比'z'大的字符
    for (int i = 0; i < n; i++) {
        if (str[i] < min_char) {
            min_char = str[i];
            min_index = i;
        }
    }
    printf("%d\n", min_index);
    return 0;
}