#include <stdio.h>
#include <string.h>

int main() {
    char key[101];
    char ciphertext[1001];
    char plaintext[1001];

    // 读取密钥和密文
    scanf("%s", key);
    scanf("%s", ciphertext);

    int key_len = strlen(key);
    int ct_len = strlen(ciphertext);

    // 加密算法实现
    for (int i = 0, j = 0; i < ct_len; i++, j++) {
        if (j >= key_len) {
            j = 0; // 密钥循环使用
        }

        char ct_char = ciphertext[i];
        char key_char = key[j];

        // 保持明文的大小写形式
        if (ct_char >= 'a' && ct_char <= 'z') {
            if (key_char >= 'A' && key_char <= 'Z') {
                key_char += 'a' - 'A'; // 转换密钥为小写
            }
            plaintext[i] = (ct_char - key_char + 26) % 26 + 'a'; // 转换为小写
        } else {
            if (key_char >= 'a' && key_char <= 'z') {
                key_char -= 'a' - 'A'; // 转换密钥为大写
            }
            plaintext[i] = (ct_char - key_char + 26) % 26 + 'A'; // 转换为大写
        }
    }

    plaintext[ct_len] = '\0'; // 字符串结束符

    // 输出明文
    printf("%s\n", plaintext);

    return 0;
}