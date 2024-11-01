#include <stdio.h>
#include <string.h>

int main() {
    char input[256];
    int a = 0, b = 0, c = 0;
    char var1, var2;
    int value;

    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, ";");
    while (token != NULL) {
        if (sscanf(token, "%c:=%c", &var1, &var2) == 2) {
            if (var2 >= '0' && var2 <= '9') {
                value = var2 - '0';
            } else {
                if (var2 == 'a') value = a;
                else if (var2 == 'b') value = b;
                else if (var2 == 'c') value = c;
            }

            if (var1 == 'a') a = value;
            else if (var1 == 'b') b = value;
            else if (var1 == 'c') c = value;
        }
        token = strtok(NULL, ";");
    }

    printf("%d %d %d\n", a, b, c);

    return 0;
}