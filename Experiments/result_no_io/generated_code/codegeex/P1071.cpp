#include <stdio.h>
#include <string.h>

int main() {
    char encrypt[101], original[101], toTranslate[101];
    scanf("%s %s %s", encrypt, original, toTranslate);

    int mapping[26]; // 用于记录每个字母的映射关系
    memset(mapping, -1, sizeof(mapping)); // 初始化为-1，表示未映射

    // 处理第一行和第二行的映射关系
    int len = strlen(encrypt);
    for (int i = 0; i < len; i++) {
        int idx1 = encrypt[i] - 'A';
        int idx2 = original[i] - 'A';

        if (mapping[idx1] == -1) {
            // 如果该字母还没有映射，则进行映射
            mapping[idx1] = idx2;
        } else if (mapping[idx1] != idx2) {
            // 如果该字母已经映射，但映射的值不一致，则说明有冲突
            printf("Failed\n");
            return 0;
        }
    }

    // 检查是否所有字母都有映射关系
    for (int i = 0; i < 26; i++) {
        if (mapping[i] == -1) {
            printf("Failed\n");
            return 0;
        }
    }

    // 使用映射关系翻译第三行加密信息
    len = strlen(toTranslate);
    for (int i = 0; i < len; i++) {
        int idx = toTranslate[i] - 'A';
        printf("%c", mapping[idx] + 'A');
    }

    return 0;
}