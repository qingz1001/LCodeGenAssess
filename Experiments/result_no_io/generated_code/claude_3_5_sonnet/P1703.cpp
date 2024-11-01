#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1001

void encrypt(char *key, char *plaintext, char *ciphertext) {
    int key_len = strlen(key);
    int plain_len = strlen(plaintext);
    
    for (int i = 0; i < plain_len; i++) {
        if (isalpha(plaintext[i])) {
            int shift = toupper(key[i % key_len]) - 'A';
            if (isupper(plaintext[i])) {
                ciphertext[i] = ((plaintext[i] - 'A' + shift) % 26) + 'A';
            } else {
                ciphertext[i] = ((plaintext[i] - 'a' + shift) % 26) + 'a';
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[plain_len] = '\0';
}

void reverse_substring(char *str, int start, int end) {
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

    scanf("%s", key);
    scanf("%s", plaintext);
    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        reverse_substring(plaintext, a - 1, b - 1);
    }

    encrypt(key, plaintext, ciphertext);
    printf("%s\n", ciphertext);

    return 0;
}