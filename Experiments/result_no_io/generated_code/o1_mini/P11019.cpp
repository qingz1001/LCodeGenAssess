#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char S[101];
    fgets(S, 101, stdin);
    int len = strlen(S);
    int start = -1, end = -1;
    for(int i=0;i<len;i++){
        if(S[i] == '['){
            start = i+1;
            break;
        }
    }
    if(start == -1){
        printf("/");
        return 0;
    }
    for(int i=start;i<len-1;i++){
        if(S[i] == ']' && S[i+1] == ']'){
            end = i;
            break;
        }
    }
    if(end == -1){
        printf("/");
        return 0;
    }
    char abbreviation[101];
    int ab_idx =0;
    for(int i=start;i<end;i++){
        if(isupper(S[i])){
            abbreviation[ab_idx++] = tolower(S[i]);
        }
    }
    abbreviation[ab_idx] = '\0';
    printf("/%s\n", abbreviation);
    return 0;
}