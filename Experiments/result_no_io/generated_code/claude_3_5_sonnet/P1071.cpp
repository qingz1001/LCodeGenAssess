#include <stdio.h>
#include <string.h>

#define MAX_LEN 101

char encrypted[MAX_LEN], original[MAX_LEN], message[MAX_LEN];
char code[26], decode[26];

int main() {
    scanf("%s%s%s", encrypted, original, message);
    
    memset(code, 0, sizeof(code));
    memset(decode, 0, sizeof(decode));
    
    int len = strlen(original);
    for (int i = 0; i < len; i++) {
        int orig = original[i] - 'A';
        int encr = encrypted[i] - 'A';
        
        if (code[orig] && code[orig] != encrypted[i]) {
            printf("Failed\n");
            return 0;
        }
        if (decode[encr] && decode[encr] != original[i]) {
            printf("Failed\n");
            return 0;
        }
        
        code[orig] = encrypted[i];
        decode[encr] = original[i];
    }
    
    for (int i = 0; i < 26; i++) {
        if (!code[i]) {
            printf("Failed\n");
            return 0;
        }
    }
    
    int msg_len = strlen(message);
    for (int i = 0; i < msg_len; i++) {
        int encr = message[i] - 'A';
        printf("%c", decode[encr]);
    }
    printf("\n");
    
    return 0;
}