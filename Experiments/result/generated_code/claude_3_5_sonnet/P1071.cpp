#include <stdio.h>
#include <string.h>

#define MAX_LEN 101

char encrypt[MAX_LEN], decrypt[MAX_LEN], message[MAX_LEN];
char code[26], decode[26];

int main() {
    scanf("%s", encrypt);
    scanf("%s", decrypt);
    scanf("%s", message);

    memset(code, 0, sizeof(code));
    memset(decode, 0, sizeof(decode));

    int len = strlen(encrypt);
    for (int i = 0; i < len; i++) {
        char e = encrypt[i] - 'A';
        char d = decrypt[i] - 'A';

        if (code[d] && code[d] != e + 'A') {
            printf("Failed\n");
            return 0;
        }
        if (decode[e] && decode[e] != d + 'A') {
            printf("Failed\n");
            return 0;
        }

        code[d] = e + 'A';
        decode[e] = d + 'A';
    }

    for (int i = 0; i < 26; i++) {
        if (!code[i]) {
            printf("Failed\n");
            return 0;
        }
    }

    for (int i = 0; message[i]; i++) {
        printf("%c", decode[message[i] - 'A']);
    }
    printf("\n");

    return 0;
}