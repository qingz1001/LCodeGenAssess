#include <stdio.h>
#include <string.h>

int main() {
    char input[4][101];
    int count[26] = {0};

    // 读取输入
    for (int i = 0; i < 4; i++) {
        fgets(input[i], sizeof(input[i]), stdin);
        for (int j = 0; j < strlen(input[i]) - 1; j++) { // 忽略换行符
            if (input[i][j] >= 'A' && input[i][j] <= 'Z') {
                count[input[i][j] - 'A']++;
            }
        }
    }

    // 找到最大出现次数
    int max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }

    // 输出柱状图
    for (int i = max_count; i > 0; i--) {
        for (int j = 0; j < 26; j++) {
            if (count[j] >= i) {
                printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }

    // 输出字母
    for (int i = 0; i < 26; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");

    return 0;
}