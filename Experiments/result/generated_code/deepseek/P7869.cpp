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

    int has_crlf = 0, has_lf = 0, has_cr = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] == '\r') {
            if (i + 1 < len && input[i + 1] == '\n') {
                has_crlf = 1;
                i++; // Skip the next '\n'
            } else {
                has_cr = 1;
            }
        } else if (input[i] == '\n') {
            has_lf = 1;
        }
    }

    if (has_crlf) {
        printf("windows\n");
    } else if (has_lf) {
        printf("linux\n");
    } else if (has_cr) {
        printf("mac\n");
    }

    return 0;
}