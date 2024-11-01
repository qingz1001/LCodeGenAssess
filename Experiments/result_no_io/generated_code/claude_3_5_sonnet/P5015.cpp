#include <stdio.h>
#include <string.h>

int main() {
    char s[501];
    int count = 0;
    
    fgets(s, sizeof(s), stdin);
    
    for (int i = 0; s[i] != '\0' && s[i] != '\n'; i++) {
        if (s[i] != ' ') {
            count++;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}