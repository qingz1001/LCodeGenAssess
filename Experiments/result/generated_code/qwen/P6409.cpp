#include <stdio.h>
#include <string.h>

int main() {
    char s[105];
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 0; i < len - 2; i++) {
        if (s[i + 1] == 'p' && (s[i + 2] == 'a' || s[i + 2] == 'e' || s[i + 2] == 'i' || s[i + 2] == 'o' || s[i + 2] == 'u')) {
            printf("%c", s[i]);
            i += 2;
        } else {
            printf("%c", s[i]);
        }
    }
    printf("%c\n", s[len - 1]);
    return 0;
}