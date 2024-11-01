#include <stdio.h>
#include <string.h>

int main() {
    char input[100001];
    fgets(input, sizeof(input), stdin);

    int len = strlen(input);
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    int has_cr = 0, has_lf = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] == '\r') {
            has_cr = 1;
        } else if (input[i] == '\n') {
            has_lf = 1;
        }
    }

    if (has_cr && has_lf) {
        printf("windows\n");
    } else if (has_cr) {
        printf("mac\n");
    } else if (has_lf) {
        printf("linux\n");
    }

    return 0;
}