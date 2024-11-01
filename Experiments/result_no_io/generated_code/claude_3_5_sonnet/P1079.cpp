#include <stdio.h>
#include <string.h>
#include <ctype.h>

char key[101], cipher[1001], plain[1001];

char decrypt(char c, char k) {
    if(isupper(c)) {
        return 'A' + (c - k + 26) % 26;
    } else {
        return 'a' + (c - tolower(k) + 26) % 26;
    }
}

int main() {
    scanf("%s", key);
    scanf("%s", cipher);
    
    int key_len = strlen(key);
    int cipher_len = strlen(cipher);
    
    for(int i = 0; i < cipher_len; i++) {
        plain[i] = decrypt(cipher[i], key[i % key_len]);
    }
    plain[cipher_len] = '\0';
    
    printf("%s\n", plain);
    
    return 0;
}