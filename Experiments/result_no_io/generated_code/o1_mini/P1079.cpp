#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char key[101], ciphertext[1001];
    scanf("%s %s", key, ciphertext);
    int key_len = strlen(key);
    int cipher_len = strlen(ciphertext);
    char plaintext[1001];
    for(int i=0; i<cipher_len; i++){
        char c = ciphertext[i];
        char k = key[i % key_len];
        if(isalpha(c) && isalpha(k)){
            int c_val = toupper(c) - 'A';
            int k_val = toupper(k) - 'A';
            int m_val = (c_val - k_val + 26) % 26;
            if(islower(c)){
                plaintext[i] = 'a' + m_val;
            }
            else{
                plaintext[i] = 'A' + m_val;
            }
        }
        else{
            plaintext[i] = c;
        }
    }
    plaintext[cipher_len] = '\0';
    printf("%s\n", plaintext);
    return 0;
}