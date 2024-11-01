#include <stdio.h>
#include <string.h>

int main() {
    char key[101], cipher[1001];
    scanf("%s %s", key, cipher);
    
    int keyLen = strlen(key);
    int cipherLen = strlen(cipher);
    
    for (int i = 0, j = 0; i < cipherLen; i++, j++) {
        if (cipher[i] >= 'a' && cipher[i] <= 'z') {
            if (key[j % keyLen] >= 'a' && key[j % keyLen] <= 'z') {
                cipher[i] = ((cipher[i] - 'a') - (key[j % keyLen] - 'a') + 26) % 26 + 'a';
            } else {
                cipher[i] = ((cipher[i] - 'a') - (key[j % keyLen] - 'A') + 26) % 26 + 'a';
            }
        } else if (cipher[i] >= 'A' && cipher[i] <= 'Z') {
            if (key[j % keyLen] >= 'a' && key[j % keyLen] <= 'z') {
                cipher[i] = ((cipher[i] - 'A') - (key[j % keyLen] - 'a') + 26) % 26 + 'A';
            } else {
                cipher[i] = ((cipher[i] - 'A') - (key[j % keyLen] - 'A') + 26) % 26 + 'A';
            }
        }
    }
    
    printf("%s\n", cipher);
    return 0;
}