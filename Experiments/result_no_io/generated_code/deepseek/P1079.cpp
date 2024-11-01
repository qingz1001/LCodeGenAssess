#include <stdio.h>
#include <string.h>

char decrypt_char(char c, char key) {
    if (c >= 'A' && c <= 'Z') {
        return (c - 'A' - (key - 'a') + 26) % 26 + 'A';
    } else if (c >= 'a' && c <= 'z') {
        return (c - 'a' - (key - 'a') + 26) % 26 + 'a';
    }
    return c;
}

int main() {
    char key[101], ciphertext[1001];
    scanf("%s", key);
    scanf("%s", ciphertext);

    int key_len = strlen(key);
    int cipher_len = strlen(ciphertext);

    for (int i = 0; i < cipher_len; i++) {
        char key_char = key[i % key_len];
        printf("%c", decrypt_char(ciphertext[i], key_char));
    }
    printf("\n");

    return 0;
}