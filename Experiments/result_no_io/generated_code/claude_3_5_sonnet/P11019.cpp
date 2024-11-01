#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char s[101];
    scanf("%s", s);
    
    printf("/");
    
    int i = 1;
    while (s[i] != ']') {
        if (isupper(s[i])) {
            putchar(tolower(s[i]));
        }
        i++;
    }
    
    return 0;
}