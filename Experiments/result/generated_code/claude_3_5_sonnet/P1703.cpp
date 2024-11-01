#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

void encrypt(char *key, char *plaintext, char *ciphertext) {
    int key_len = strlen(key);
    int text_len = strlen(plaintext);
    
    for (int i = 0; i < text_len; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int shift = tolower(key[i % key_len]) - 'a';
            ciphertext[i] = (plaintext[i] - base + shift) % 26 + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[text_len] = '\0';
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

    fgets(key, MAX_LEN, stdin);
    key[strcspn(key, "\n")] = 0;

    fgets(plaintext, MAX_LEN, stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;

    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        reverse_substring(plaintext, a - 1, b - 1);
    }

    encrypt(key, plaintext, ciphertext);
    printf("%s\n", ciphertext);

    return 0;
}