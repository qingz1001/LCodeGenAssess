#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char equation[1000001];
    fgets(equation, sizeof(equation), stdin);

    // Remove spaces
    int len = strlen(equation);
    if (equation[len - 1] == '\n') equation[len - 1] = '\0';
    len = strlen(equation);

    char *ptr = equation;
    while (*ptr) {
        if (isspace(*ptr)) {
            memmove(ptr, ptr + 1, len - (ptr - equation));
            len--;
        } else {
            ptr++;
        }
    }

    int x, y, z;
    char op;
    char *x_str, *y_str, *z_str;

    if (strstr(equation, "+") != NULL) {
        op = '+';
        x_str = strtok(equation, "+=");
        y_str = strtok(NULL, "+=");
        z_str = strtok(NULL, "+=");
    } else {
        op = '-';
        x_str = strtok(equation, "-=");
        y_str = strtok(NULL, "-=");
        z_str = strtok(NULL, "-=");
    }

    if (strcmp(x_str, "?") == 0) {
        y = atoi(y_str);
        z = atoi(z_str);
        if (op == '+') {
            x = z - y;
        } else {
            x = z + y;
        }
        printf("%d\n", x);
    } else if (strcmp(y_str, "?") == 0) {
        x = atoi(x_str);
        z = atoi(z_str);
        if (op == '+') {
            y = z - x;
        } else {
            y = x - z;
        }
        printf("%d\n", y);
    } else {
        x = atoi(x_str);
        y = atoi(y_str);
        if (op == '+') {
            z = x + y;
        } else {
            z = x - y;
        }
        printf("%d\n", z);
    }

    return 0;
}