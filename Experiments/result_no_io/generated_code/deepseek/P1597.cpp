#include <stdio.h>
#include <string.h>

int main() {
    char input[256];
    int a = 0, b = 0, c = 0;
    int i, len;
    char var1, var2, value;

    fgets(input, sizeof(input), stdin);
    len = strlen(input);

    for (i = 0; i < len; i++) {
        if (input[i] == ':') {
            var1 = input[i - 1];
            var2 = input[i + 2];

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
    }

    printf("%d %d %d\n", a, b, c);
    return 0;
}