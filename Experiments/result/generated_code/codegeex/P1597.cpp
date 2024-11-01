#include <stdio.h>
#include <string.h>

int main() {
    char input[256];
    int a = 0, b = 0, c = 0;
    int temp;
    char var, op;

    fgets(input, sizeof(input), stdin);
    char *token = strtok(input, ";");

    while (token != NULL) {
        sscanf(token, "%c:=%d", &var, &temp);
        if (var == 'a') {
            a = temp;
        } else if (var == 'b') {
            b = temp;
        } else if (var == 'c') {
            c = temp;
        }
        token = strtok(NULL, ";");
    }

    printf("%d %d %d\n", a, b, c);

    return 0;
}