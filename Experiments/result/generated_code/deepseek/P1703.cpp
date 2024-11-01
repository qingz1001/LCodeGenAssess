#include <stdio.h>
#include <string.h>

void reverseSubstring(char *str, int a, int b) {
    while (a < b) {
        char temp = str[a];
        str[a] = str[b];
        str[b] = temp;
        a++;
        b--;
    }
}

int main() {
    char key[101], plaintext[1001];
    int M, a, b;

    scanf("%s", key);
    scanf("%s", plaintext);
    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        reverseSubstring(plaintext, a - 1, b - 1);
    }

    int keyLen = strlen(key);
    int plainLen = strlen(plaintext);

    for (int i = 0; i < plainLen; i++) {
        int keyIndex = i % keyLen;
        int shift = key[keyIndex] - 'A';
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
        }
    }

    printf("%s\n", plaintext);

    return 0;
}