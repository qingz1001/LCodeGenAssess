#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    fgets(s, sizeof(s), stdin);
    
    int count = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] != ' ' && s[i] != '\n') {
            count++;
        }
    }
    
    printf("%d\n", count);
    return 0;
}