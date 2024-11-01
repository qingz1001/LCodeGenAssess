#include <stdio.h>
#include <string.h>

int main() {
    char key[101];
    char ciphertext[1001];
    char plaintext[1001];

    scanf("%s", key);
    scanf("%s", ciphertext);

    int key_len = strlen(key);
    int cipher_len = strlen(ciphertext);

    for (int i = 0; i < cipher_len; i++) {
        char k = key[i % key_len];
        if (isalpha(k)) {
            k = tolower(k) - 'a';
        } else {
            k -= 'A' - 'a';
        }

        char c = ciphertext[i];
        if (isalpha(c)) {
            c = tolower(c) - 'a';
            plaintext[i] = 'a' + (c - k + 26) % 26;
        } else {
            plaintext[i] = 'A' + (c - k + 26) % 26;
        }
    }

    plaintext[cipher_len] = '\0';
    printf("%s\n", plaintext);

    return 0;
}