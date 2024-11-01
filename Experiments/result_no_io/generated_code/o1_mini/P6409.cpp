#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) {
    return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
}

int main(){
    char s[101];
    char result[101];
    fgets(s, sizeof(s), stdin);
    int len = strlen(s);
    if(s[len-1] == '\n') s[len-1] = '\0';
    int i=0, j=0;
    while(s[i]){
        if(is_vowel(s[i])){
            result[j++] = s[i];
            i +=3;
        }
        else{
            result[j++] = s[i++];
        }
    }
    result[j] = '\0';
    printf("%s", result);
    return 0;
}