#include <stdio.h>

int main(){
    char s[100];
    if (fgets(s, sizeof(s), stdin) != NULL){
        int count = 0;
        for(int i = 0; s[i] != '\0'; i++){
            if(s[i] != ' ' && s[i] != '\n'){
                count++;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}