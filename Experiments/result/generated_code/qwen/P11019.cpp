#include <stdio.h>
#include <string.h>

int main() {
    char input[101];
    scanf("%s", input);

    int length = strlen(input);
    char result[50] = "/";

    for (int i = 1; i < length - 7; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            result[strlen(result)] = tolower(input[i]);
        }
    }

    printf("%s\n", result);

    return 0;
}