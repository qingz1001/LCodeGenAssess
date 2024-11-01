#include <stdio.h>
#include <string.h>
#include <ctype.h>

char decrypt_char(char c, char key) {
    int shift = tolower(key) - 'a';
    if (isupper(c)) {
        return (c - 'A' - shift + 26) % 26 + 'A';
    } else {
        return (c - 'a' - shift + 26) % 26 + 'a';
    }
}

int main() {
    char key[101];
    char ciphertext[1001];
    char plaintext[1001];

    scanf("%s", key);
    scanf("%s", ciphertext);

    int key_len = strlen(key);
    int cipher_len = strlen(ciphertext);

    for (int i = 0; i < cipher_len; i++) {
        plaintext[i] = decrypt_char(ciphertext[i], key[i % key_len]);
    }
    plaintext[cipher_len] = '\0';

    printf("%s\n", plaintext);

    return 0;
}