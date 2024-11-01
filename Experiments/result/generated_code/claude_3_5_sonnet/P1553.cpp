#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void trim_zeros(char *str) {
    int len = strlen(str);
    int i = len - 1;
    while (i > 0 && str[i] == '0') {
        str[i] = '\0';
        i--;
    }
    if (str[i] == '.') str[i] = '\0';
}

void reverse_integer(char *str) {
    reverse_string(str);
    while (str[0] == '0' && str[1] != '\0') {
        memmove(str, str + 1, strlen(str));
    }
}

void reverse_decimal(char *str) {
    char *decimal_point = strchr(str, '.');
    if (decimal_point) {
        *decimal_point = '\0';
        reverse_integer(str);
        reverse_string(decimal_point + 1);
        *decimal_point = '.';
        trim_zeros(str);
    } else {
        reverse_integer(str);
    }
}

void reverse_fraction(char *str) {
    char *slash = strchr(str, '/');
    if (slash) {
        *slash = '\0';
        reverse_integer(str);
        reverse_integer(slash + 1);
        *slash = '/';
    }
}

void reverse_percentage(char *str) {
    int len = strlen(str);
    str[len - 1] = '\0';
    reverse_integer(str);
    str[len - 1] = '%';
}

int main() {
    char s[100];
    scanf("%s", s);

    if (strchr(s, '%')) {
        reverse_percentage(s);
    } else if (strchr(s, '/')) {
        reverse_fraction(s);
    } else if (strchr(s, '.')) {
        reverse_decimal(s);
    } else {
        reverse_integer(s);
    }

    printf("%s\n", s);
    return 0;
}