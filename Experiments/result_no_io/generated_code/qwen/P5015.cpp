#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    int length, count = 0;

    fgets(s, sizeof(s), stdin);
    length = strlen(s);

    for (int i = 0; i < length - 1; i++) { // Subtract 1 to exclude the newline character
        if (s[i] != ' ' && s[i] != '\n') {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}