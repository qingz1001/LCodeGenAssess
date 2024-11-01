#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char key[1000], plaintext[1000];
    int M, a, b;
    scanf("%s", key);
    scanf("%s", plaintext);
    scanf("%d", &M);

    // 密钥规范化
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        if (islower(key[i])) {
            key[i] = key[i] - 'a' + 'A';
        }
    }

    // 密文生成
    int p_len = strlen(plaintext);
    char ciphertext[p_len + 1];
    for (int i = 0, j = 0; i < p_len; i++, j++) {
        if (j == len) j = 0;
        if (islower(plaintext[i])) {
            ciphertext[i] = (plaintext[i] - 'a' + key[j] - 'A') % 26 + 'a';
        } else {
            ciphertext[i] = (plaintext[i] - 'A' + key[j] - 'A') % 26 + 'A';
        }
    }
    ciphertext[p_len] = '\0';

    // 执行操作
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        for (int j = a - 1; j < b; j++) {
            char temp = ciphertext[j];
            ciphertext[j] = ciphertext[b - 1];
            ciphertext[b - 1] = temp;
            b--;
        }
    }

    // 输出密文
    printf("%s\n", ciphertext);

    return 0;
}