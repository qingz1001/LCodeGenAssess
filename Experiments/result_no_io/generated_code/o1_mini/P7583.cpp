#include <stdio.h>

int main(){
    char s[101], result[101];
    int i, j=0;
    scanf("%s", s);
    for(i=0; s[i]!='\0'; i++){
        char c = s[i];
        if(c != 'C' && c != 'A' && c != 'M' && c != 'B' && c != 'R' && c != 'I' && c != 'D' && c != 'G' && c != 'E'){
            result[j++] = c;
        }
    }
    result[j] = '\0';
    printf("%s\n", result);
    return 0;
}