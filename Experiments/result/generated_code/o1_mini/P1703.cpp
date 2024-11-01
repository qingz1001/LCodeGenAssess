#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX 100005

int main(){
    char key[MAX], plaintext[MAX];
    fgets(key, MAX, stdin);
    size_t len = strlen(key);
    if(key[len-1]=='\n') key[len-1]='\0';
    fgets(plaintext, MAX, stdin);
    len = strlen(plaintext);
    if(plaintext[len-1]=='\n') plaintext[len-1]='\0';
    int M;
    scanf("%d", &M);
    for(int i=0;i<M;i++){
        int a,b;
        scanf("%d %d", &a, &b);
        a--; b--;
        while(a < b){
            char tmp = plaintext[a];
            plaintext[a] = plaintext[b];
            plaintext[b] = tmp;
            a++;
            b--;
        }
    }
    int key_len = strlen(key);
    int pt_len = strlen(plaintext);
    char ciphertext[MAX];
    for(int i=0;i<pt_len;i++){
        if(isalpha(plaintext[i])){
            int shift;
            if(isupper(key[i % key_len])) shift = key[i % key_len] - 'A';
            else shift = key[i % key_len] - 'a';
            if(isupper(plaintext[i])){
                ciphertext[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
            }
            else{
                ciphertext[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
            }
        }
        else{
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[pt_len]='\0';
    printf("%s\n", ciphertext);
}