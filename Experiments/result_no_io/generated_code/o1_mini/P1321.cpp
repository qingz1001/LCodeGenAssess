#include <stdio.h>
#include <string.h>

int main(){
    char s[256];
    int boy=0, girl=0, len, i;
    fgets(s, sizeof(s), stdin);
    len = strlen(s);
    if(s[len-1]=='\n') s[len-1]='\0';
    len = strlen(s);
    for(i=0;i<len;i++){
        if(i+2 < len){
            if(s[i]=='b' && s[i+1]=='o' && s[i+2]=='y') boy++;
        }
        if(i+3 < len){
            if(s[i]=='g' && s[i+1]=='i' && s[i+2]=='r' && s[i+3]=='l') girl++;
        }
    }
    printf("%d\n%d", boy, girl);
    return 0;
}