#include <stdio.h>
#include <string.h>

int main() {
    int n;
    char str[51];
    
    scanf("%d", &n);
    scanf("%s", str);
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = ((str[i] - 'a' + n) % 26) + 'a';
        }
    }
    
    printf("%s\n", str);
    
    return 0;
}