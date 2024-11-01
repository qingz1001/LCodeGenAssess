#include <stdio.h>
#include <string.h>

int main(){
    char s[300];
    fgets(s, sizeof(s), stdin);
    int len = strlen(s);
    if(s[len-1] == '\n') s[len-1] = '\0';
    len = strlen(s);
    int cnt_boy = 0, cnt_girl = 0;
    for(int i=0;i<len;i++){
        if(i+2 < len && s[i]=='b' && s[i+1]=='o' && s[i+2]=='y'){
            cnt_boy++;
        }
        if(i+3 < len && s[i]=='g' && s[i+1]=='i' && s[i+2]=='r' && s[i+3]=='l'){
            cnt_girl++;
        }
    }
    printf("%d\n%d\n", cnt_boy, cnt_girl);
}