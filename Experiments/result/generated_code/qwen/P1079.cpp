#include <stdio.h>
#include <string.h>

void decrypt(char *key, char *cipher, char *plain) {
    int key_len = strlen(key);
    int cipher_len = strlen(cipher);
    for (int i = 0; i < cipher_len; i++) {
        if (isalpha(cipher[i])) {
            char base = islower(cipher[i]) ? 'a' : 'A';
            plain[i] = ((cipher[i] - base - (key[i % key_len] - base + 26)) % 26) + base;
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[cipher_len] = '\0';
}

int main() {
    char key[101], cipher[1001], plain[1001];
    scanf("%s", key);
    scanf("%s", cipher);
    decrypt(key, cipher, plain);
    printf("%s\n", plain);
    return 0;
}