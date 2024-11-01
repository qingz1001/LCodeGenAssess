#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char equation[1000001];
    fgets(equation, sizeof(equation), stdin);

    // Remove leading and trailing spaces
    while (equation[0] == ' ') {
        memmove(equation, equation + 1, strlen(equation));
    }
    while (equation[strlen(equation) - 1] == ' ' || equation[strlen(equation) - 1] == '\n') {
        equation[strlen(equation) - 1] = '\0';
    }

    // Find the positions of '+' and '='
    char *plus_pos = strchr(equation, '+');
    char *minus_pos = strchr(equation, '-');
    char *equal_pos = strchr(equation, '=');

    if (plus_pos != NULL && equal_pos != NULL) {
        // X + Y = Z
        char *x_str = strtok(equation, "+=");
        char *y_str = strtok(NULL, "=");
        char *z_str = strtok(NULL, "");

        // Remove spaces
        x_str = strtok(x_str, " ");
        y_str = strtok(y_str, " ");
        z_str = strtok(z_str, " ");

        int x, y, z;
        if (strcmp(x_str, "?") == 0) {
            y = atoi(y_str);
            z = atoi(z_str);
            printf("%d\n", z - y);
        } else if (strcmp(y_str, "?") == 0) {
            x = atoi(x_str);
            z = atoi(z_str);
            printf("%d\n", z - x);
        } else if (strcmp(z_str, "?") == 0) {
            x = atoi(x_str);
            y = atoi(y_str);
            printf("%d\n", x + y);
        }
    } else if (minus_pos != NULL && equal_pos != NULL) {
        // X - Y = Z
        char *x_str = strtok(equation, "-=");
        char *y_str = strtok(NULL, "=");
        char *z_str = strtok(NULL, "");

        // Remove spaces
        x_str = strtok(x_str, " ");
        y_str = strtok(y_str, " ");
        z_str = strtok(z_str, " ");

        int x, y, z;
        if (strcmp(x_str, "?") == 0) {
            y = atoi(y_str);
            z = atoi(z_str);
            printf("%d\n", z + y);
        } else if (strcmp(y_str, "?") == 0) {
            x = atoi(x_str);
            z = atoi(z_str);
            printf("%d\n", x - z);
        } else if (strcmp(z_str, "?") == 0) {
            x = atoi(x_str);
            y = atoi(y_str);
            printf("%d\n", x - y);
        }
    }

    return 0;
}