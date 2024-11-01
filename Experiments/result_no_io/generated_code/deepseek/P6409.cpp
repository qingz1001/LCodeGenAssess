#include <stdio.h>
#include <string.h>

int is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
    char s[101];
    scanf("%[^\n]", s);

    int len = strlen(s);
    char result[101] = "";
    int j = 0;

    for (int i = 0; i < len; i++) {
        result[j++] = s[i];
        if (is_vowel(s[i]) && i + 2 < len && s[i+1] == 'p' && s[i+2] == s[i]) {
            i += 2;
        }
    }
    result[j] = '\0';

    printf("%s\n", result);
    return 0;
}