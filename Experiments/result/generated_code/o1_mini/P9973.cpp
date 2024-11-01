#include <stdio.h>
#include <string.h>

int main(){
    char s[201];
    if(!fgets(s, sizeof(s), stdin)){
        printf("Human\n");
        return 0;
    }
    // Remove trailing newline if present
    size_t len = strlen(s);
    if(len >0 && s[len-1]=='\n') s[len-1]='\0';
    const char prefix[] = "You are right, but ";
    if(strlen(s) >=19 && strncmp(s, prefix, 19) ==0){
        printf("AI\n");
    }
    else{
        printf("Human\n");
    }
}