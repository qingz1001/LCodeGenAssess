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
    char key[101], plaintext[101];
    int M, a, b;

    scanf("%s", key);
    scanf("%s", plaintext);
    scanf("%d", &M);

    int len = strlen(plaintext);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        reverseSubstring(plaintext, a - 1, b - 1);
    }

    for (int i = 0; i < len; i++) {
        int shift = key[i % strlen(key)] - 'A';
        plaintext[i] = (plaintext[i] - 'A' - shift + 26) % 26 + 'A';
    }

    printf("%s\n", plaintext);

    return 0;
}