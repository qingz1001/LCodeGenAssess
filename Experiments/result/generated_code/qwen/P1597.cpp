#include <stdio.h>
#include <string.h>

int main() {
    char code[256];
    int a = 0, b = 0, c = 0;

    fgets(code, sizeof(code), stdin);

    // Parse the code and update the variables
    for (char *token = strtok(code, ";"); token != NULL; token = strtok(NULL, ";")) {
        if (strncmp(token, "a:=", 3) == 0) {
            sscanf(&token[3], "%d", &a);
        } else if (strncmp(token, "b:=", 3) == 0) {
            sscanf(&token[3], "%d", &b);
        } else if (strncmp(token, "c:=", 3) == 0) {
            sscanf(&token[3], "%d", &c);
        }
    }

    // Output the final values of a, b, and c
    printf("%d %d %d\n", a, b, c);

    return 0;
}