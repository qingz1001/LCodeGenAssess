#include <stdio.h>
#include <string.h>

int main() {
    int n;
    char str[51];
    
    scanf("%d", &n);
    scanf("%s", str);
    
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = (str[i] - 'a' + n) % 26 + 'a';
    }
    
    printf("%s\n", str);
    
    return 0;
}