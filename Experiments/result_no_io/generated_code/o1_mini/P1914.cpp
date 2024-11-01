#include <stdio.h>
#include <string.h>

int main(){
    int n;
    char s[51];
    scanf("%d", &n);
    scanf("%s", s);
    int len = strlen(s);
    for(int i=0;i<len;i++){
        s[i] = 'a' + (s[i] - 'a' + n) % 26;
    }
    printf("%s\n", s);
    return 0;
}