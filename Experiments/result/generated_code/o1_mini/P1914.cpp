#include <stdio.h>

int main(){
    int n;
    char s[51], res[51];
    scanf("%d", &n);
    scanf("%s", s);
    int i=0;
    while(s[i]!='\0'){
        res[i] = 'a' + (s[i]-'a' + n) % 26;
        i++;
    }
    res[i] = '\0';
    printf("%s\n", res);
    return 0;
}