#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

void reverse_segment(char *str, int start, int end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int main() {
    char key[MAX_LEN], plaintext[MAX_LEN], ciphertext[MAX_LEN];
    int M, a, b;

    // 读取密钥
    scanf("%s", key);
    // 读取明文
    scanf("%s", plaintext);

    // 计算密文
    int key_len = strlen(key);
    int text_len = strlen(plaintext);
    int j = 0;
    for (int i = 0; i < text_len; i++) {
        if (isalpha(plaintext[i])) {
            if (islower(plaintext[i])) {
                ciphertext[i] = (tolower(key[j]) - 'a' + tolower(plaintext[i]) - 'a') % 26 + 'a';
            } else {
                ciphertext[i] = (toupper(key[j]) - 'A' + toupper(plaintext[i]) - 'A') % 26 + 'A';
            }
            j = (j + 1) % key_len;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[text_len] = '\0';

    // 读取操作个数
    scanf("%d", &M);

    // 执行操作
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        reverse_segment(ciphertext, a, b);
    }

    // 输出密文
    printf("%s\n", ciphertext);

    return 0;
}