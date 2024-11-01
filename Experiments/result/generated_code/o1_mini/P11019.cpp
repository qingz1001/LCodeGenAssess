#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char S[105];
    fgets(S, sizeof(S), stdin);
    S[strcspn(S, "\n")] = 0;

    char *start = strchr(S, '[');
    if(start != NULL){
        start++; // Move past '['
        char *end = strstr(start, "]]");
        if(end != NULL){
            char result[100] = "";
            for(char *p = start; p < end; p++){
                if(isupper(*p)){
                    char c = tolower(*p);
                    int len = strlen(result);
                    result[len] = c;
                    result[len+1] = '\0';
                }
            }
            printf("/%s\n", result);
        }
    }
    return 0;
}