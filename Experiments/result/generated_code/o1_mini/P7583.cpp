#include <stdio.h>
#include <string.h>

int main(){
    char s[101];
    scanf("%100s", s);
    int delete_map[26] = {0};
    char delete_chars[] = "CAMBRIDGE";
    for(int i=0; delete_chars[i]!='\0'; i++){
        delete_map[delete_chars[i]-'A'] = 1;
    }
    int len = strlen(s);
    for(int i=0; i<len; i++){
        if(!delete_map[s[i]-'A']){
            printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}