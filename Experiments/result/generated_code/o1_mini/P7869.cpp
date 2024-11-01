#include <stdio.h>
#include <string.h>

int main(){
    char s[100005];
    if(fgets(s, sizeof(s), stdin) == NULL){
        return 0;
    }
    int len = strlen(s);
    // Remove trailing newline if present
    if(len > 0 && s[len-1] == '\n'){
        s[len-1] = '\0';
        len--;
    }
    for(int i = 0; i < len; i++){
        if(s[i] == '\\'){
            if(i + 1 < len){
                if(s[i+1] == 'r'){
                    if(i + 3 < len && s[i+2] == '\\' && s[i+3] == 'n'){
                        printf("windows");
                        return 0;
                    }
                    else{
                        printf("mac");
                        return 0;
                    }
                }
                else if(s[i+1] == 'n'){
                    printf("linux");
                    return 0;
                }
            }
        }
    }
    return 0;
}