#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000005

int main(){
    char key[MAX_LEN];
    char plaintext[MAX_LEN];
    char ciphertext[MAX_LEN];
    int M;
    // Read key
    scanf("%s", key);
    // Read plaintext
    scanf("%s", plaintext);
    // Copy plaintext to ciphertext
    strcpy(ciphertext, plaintext);
    // Read M
    scanf("%d", &M);
    for(int i=0;i<M;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        // Convert to 0-based index
        a--;
        b--;
        // Reverse substring from a to b
        while(a < b){
            char temp = ciphertext[a];
            ciphertext[a] = ciphertext[b];
            ciphertext[b] = temp;
            a++;
            b--;
        }
    }
    // Output ciphertext
    printf("%s\n", ciphertext);
    return 0;
}