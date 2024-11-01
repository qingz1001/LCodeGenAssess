#include <stdio.h>

int main() {
    int count[26] = {0};
    char ch;
    FILE *file;

    // 打开输入文件
    file = fopen("input.txt", "r");

    // 读取四行字符并统计每个字符出现的次数
    for (int i = 0; i < 4; i++) {
        while ((ch = fgetc(file)) != EOF) {
            if (ch >= 'A' && ch <= 'Z') {
                count[ch - 'A']++;
            }
        }
    }

    // 关闭输入文件
    fclose(file);

    // 打印柱状图
    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            printf("*");
            for (int j = 0; j < count[i]; j++) {
                printf(" ");
            }
            printf("\n");
        }
    }

    // 打印字母表
    printf(" ");
    for (int i = 0; i < 26; i++) {
        printf("%c", 'A' + i);
    }
    printf("\n");

    return 0;
}