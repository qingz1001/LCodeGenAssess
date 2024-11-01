#include <stdio.h>
#include <string.h>

int main() {
    char encrypted[101], original[101], message[101];
    int mapping[26] = {0}; // 用于记录映射关系，0表示未映射
    int used[26] = {0}; // 用于记录原信息中的字母是否出现过
    int i, j;

    // 读取输入
    scanf("%s%s%s", encrypted, original, message);

    // 处理原信息中的字母
    for (i = 0; i < strlen(original); i++) {
        used[original[i] - 'A'] = 1;
    }

    // 处理加密信息与原信息的映射关系
    for (i = 0; i < strlen(encrypted); i++) {
        int enc = encrypted[i] - 'A';
        int ori = original[i] - 'A';

        if (mapping[enc] == 0) {
            mapping[enc] = ori;
        } else if (mapping[enc] != ori) {
            printf("Failed\n");
            return 0;
        }

        if (used[ori] == 0) {
            printf("Failed\n");
            return 0;
        }
    }

    // 检查是否所有字母都映射了
    for (i = 0; i < 26; i++) {
        if (mapping[i] == 0) {
            printf("Failed\n");
            return 0;
        }
    }

    // 使用映射关系解密第三行信息
    for (i = 0; i < strlen(message); i++) {
        int index = message[i] - 'A';
        printf("%c", mapping[index] + 'A');
    }

    printf("\n");
    return 0;
}