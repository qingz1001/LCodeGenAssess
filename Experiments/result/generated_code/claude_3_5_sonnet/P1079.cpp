#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEY_LEN 101
#define MAX_TEXT_LEN 1001

char key[MAX_KEY_LEN];
char ciphertext[MAX_TEXT_LEN];
char plaintext[MAX_TEXT_LEN];

char decrypt(char c, char k) {
    if (!isalpha(c)) return c;
    
    char base = isupper(c) ? 'A' : 'a';
    return (c - k + 26) % 26 + base;
}

int main() {
    fgets(key, MAX_KEY_LEN, stdin);
    key[strcspn(key, "\n")] = 0;  // Remove newline
    
    fgets(ciphertext, MAX_TEXT_LEN, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;  // Remove newline

    int key_len = strlen(key);
    int text_len = strlen(ciphertext);
    
    for (int i = 0; i < text_len; i++) {
        char k = tolower(key[i % key_len]);
        plaintext[i] = decrypt(ciphertext[i], k - 'a');
    }
    plaintext[text_len] = '\0';
    
    printf("%s\n", plaintext);
    
    return 0;
}