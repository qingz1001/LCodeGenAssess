#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char key[105], ciphertext[1005];
    scanf("%s", key);
    scanf("%s", ciphertext);
    int key_len = strlen(key);
    int text_len = strlen(ciphertext);
    char plaintext[1005];
    for(int i=0;i<text_len;i++){
        char kc = key[i % key_len];
        int shift;
        if('a' <= kc && kc <= 'z') shift = kc - 'a';
        else shift = kc - 'A';
        char cc = ciphertext[i];
        if('A' <= cc && cc <= 'Z'){
            plaintext[i] = (cc - 'A' - shift + 26) % 26 + 'A';
        }
        else if('a' <= cc && cc <= 'z'){
            plaintext[i] = (cc - 'a' - shift + 26) % 26 + 'a';
        }
    }
    plaintext[text_len] = '\0';
    printf("%s", plaintext);
    return 0;
}