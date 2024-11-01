#include <stdio.h>
#include <ctype.h>

int main() {
    char s[101];
    scanf("%s", s);
    
    printf("/");
    
    int i = 1;  // 跳过开头的'['
    while (s[i] != ']') {
        if (isupper(s[i])) {
            printf("%c", tolower(s[i]));
        }
        i++;
    }
    
    return 0;
}