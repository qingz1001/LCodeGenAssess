#include <stdio.h>
#include <string.h>
#include <math.h>

void reverseString(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}

int main() {
    char input[100];
    scanf("%s", input);

    char *dot = strchr(input, '.');
    char *slash = strchr(input, '/');
    char *percent = strchr(input, '%');

    if (dot != NULL) {
        // Reverse the integer part
        reverseString(input);
        // Reverse the decimal part
        reverseString(dot + 1);
        // Reinsert the decimal point
        char temp = *dot;
        *dot = *dot + 1;
        *(dot + 1) = temp;
    } else if (slash != NULL) {
        // Reverse the numerator
        reverseString(input);
        // Reverse the denominator
        reverseString(slash + 1);
        // Reinsert the slash
        char temp = *slash;
        *slash = *slash + 1;
        *(slash + 1) = temp;
    } else if (percent != NULL) {
        // Reverse the percent part
        reverseString(input);
        // Reinsert the percent sign
        char temp = *percent;
        *percent = *percent + 1;
        *(percent + 1) = temp;
    } else {
        // Reverse the integer
        reverseString(input);
    }

    printf("%s\n", input);
    return 0;
}