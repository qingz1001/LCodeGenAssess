#include <stdio.h>
#include <string.h>

#define MAX_LEN 100005

int main(){
    char buffer[MAX_LEN];
    int idx = 0;
    int c;
    while((c = getchar()) != EOF){
        if(idx < MAX_LEN -1){
            buffer[idx++] = c;
        }
    }
    buffer[idx] = '\0';
    
    if(strstr(buffer, "\\r\\n") != NULL){
        printf("windows");
    }
    else if(strstr(buffer, "\\n") != NULL){
        printf("linux");
    }
    else{
        printf("mac");
    }
    return 0;
}