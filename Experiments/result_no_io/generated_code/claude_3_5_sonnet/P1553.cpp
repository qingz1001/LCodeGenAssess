#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 25

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
    while (len > 1 && str[len - 1] == '0') {
        str[len - 1] = '\0';
        len--;
    }
}

void reverse_integer(char *str) {
    reverse_string(str);
    while (str[0] == '0' && str[1] != '\0') {
        memmove(str, str + 1, strlen(str));
    }
}

void reverse_decimal(char *str) {
    char *dot = strchr(str, '.');
    if (dot) {
        *dot = '\0';
        reverse_integer(str);
        reverse_string(dot + 1);
        trim_zeros(dot + 1);
        *dot = '.';
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
    char s[MAX_LEN];
    scanf("%s", s);

    if (strchr(s, '%')) {
        reverse_percentage(s);
    } else if (strchr(s, '/')) {
        reverse_fraction(s);
    } else {
        reverse_decimal(s);
    }

    printf("%s\n", s);
    return 0;
}