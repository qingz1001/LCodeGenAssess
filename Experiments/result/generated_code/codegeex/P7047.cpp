#include <stdio.h>

int main() {
    char input[200];
    scanf("%s", input);

    // 遍历所有可能的长度为 n 的 01 串
    for (int i = 0; i < (1 << 26); i++) {
        char output[200];
        for (int j = 0; j < 26; j++) {
            output[j] = (i & (1 << j)) ? '1' : '0';
        }

        // 输出长度为 n 的 01 串
        printf("%s\n", output);
    }

    return 0;
}