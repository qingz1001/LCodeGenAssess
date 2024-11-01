#include <stdio.h>
#include <string.h>

int main() {
    char input[100001];
    scanf("%s", input);

    int len = strlen(input);
    int hasCR = 0, hasLF = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] == '\\' && i + 1 < len) {
            if (input[i + 1] == 'n') hasLF = 1;
            else if (input[i + 1] == 'r') hasCR = 1;
            i++; // Skip the next character as it's part of the escape sequence
        }
    }

    if (hasCR && hasLF) printf("mixed\n");
    else if (hasCR) printf("mac\n");
    else if (hasLF) printf("linux\n");
    else printf("unknown\n");

    return 0;
}