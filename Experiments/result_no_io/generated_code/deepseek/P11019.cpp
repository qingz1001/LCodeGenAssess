#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char S[101];
    scanf("%s", S);

    int len = strlen(S);
    char result[101];
    int result_index = 0;

    // 找到第一个 ']' 的位置
    int i = 0;
    while (S[i] != ']') {
        if (isupper(S[i])) {
            result[result_index++] = tolower(S[i]);
        }
        i++;
    }

    result[result_index++] = '/';

    // 复制拼音缩写
    for (int j = 0; j < result_index - 1; j++) {
        result[result_index++] = result[j];
    }

    result[result_index] = '\0';

    printf("%s\n", result);

    return 0;
}