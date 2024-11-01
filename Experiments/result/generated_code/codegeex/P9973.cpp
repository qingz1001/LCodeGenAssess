#include <stdio.h>
#include <string.h>

int main() {
    char s[201];
    scanf("%s", s);
    int len = strlen(s);
    
    if (len < 19) {
        printf("Human\n");
        return 0;
    }
    
    int prefix_count = 0;
    for (int i = 0; i < 19; i++) {
        if (s[i] == 'Y' || s[i] == 'y' || s[i] == 'o' || s[i] == 'u' || s[i] == ' ' || s[i] == 'a' || s[i] == 'r' || s[i] == 'e') {
            prefix_count++;
        }
    }
    
    if (prefix_count == 19) {
        printf("AI\n");
    } else {
        printf("Human\n");
    }
    
    return 0;
}