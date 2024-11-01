#include <stdio.h>
#include <ctype.h>

int main() {
    char s[100];
    fgets(s, sizeof(s), stdin);

    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isspace(s[i])) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}