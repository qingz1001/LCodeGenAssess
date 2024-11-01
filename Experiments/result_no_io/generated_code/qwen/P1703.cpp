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
    char key[100], plaintext[100];
    int M, a, b;

    scanf("%s", key);
    scanf("%s", plaintext);
    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        reverseSubstring(plaintext, a - 1, b - 1);
    }

    printf("%s\n", plaintext);

    return 0;
}