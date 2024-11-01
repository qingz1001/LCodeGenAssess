#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void removeLeadingZeros(char *str) {
    int i = 0;
    while (str[i] == '0' && str[i + 1] != '\0') i++;
    memmove(str, str + i, strlen(str + i) + 1);
}

void removeTrailingZeros(char *str) {
    int len = strlen(str);
    while (len > 1 && str[len - 1] == '0') {
        str[len - 1] = '\0';
        len--;
    }
}

void reverseInteger(char *str) {
    reverseString(str);
    removeLeadingZeros(str);
}

void reverseDecimal(char *str) {
    char *dot = strchr(str, '.');
    if (dot) {
        *dot = '\0';
        reverseInteger(str);
        reverseInteger(dot + 1);
        removeTrailingZeros(dot + 1);
        *dot = '.';
    } else {
        reverseInteger(str);
    }
}

void reverseFraction(char *str) {
    char *slash = strchr(str, '/');
    if (slash) {
        *slash = '\0';
        reverseInteger(str);
        reverseInteger(slash + 1);
        *slash = '/';
    } else {
        reverseInteger(str);
    }
}

void reversePercentage(char *str) {
    str[strlen(str) - 1] = '\0';
    reverseInteger(str);
    strcat(str, "%");
}

int main() {
    char input[100];
    scanf("%s", input);

    if (strchr(input, '.')) {
        reverseDecimal(input);
    } else if (strchr(input, '/')) {
        reverseFraction(input);
    } else if (strchr(input, '%')) {
        reversePercentage(input);
    } else {
        reverseInteger(input);
    }

    printf("%s\n", input);
    return 0;
}