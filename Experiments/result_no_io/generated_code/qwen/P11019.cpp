#include <stdio.h>
#include <string.h>

int main() {
    char input[101];
    scanf("%s", input);

    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        if (input[i] == ']') {
            printf("/");
            break;
        }
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
            printf("%c", tolower(input[i]));
        }
    }

    return 0;
}