#include <stdio.h>
#include <string.h>

int main() {
    char input[100001];
    scanf("%s", input);

    int len = strlen(input);
    int found_crlf = 0, found_cr = 0, found_lf = 0;

    for (int i = 0; i < len - 1; i++) {
        if (input[i] == '\\' && input[i + 1] == 'n') {
            found_lf = 1;
        } else if (input[i] == '\\' && input[i + 1] == 'r' && input[i + 2] == '\\') {
            found_cr = 1;
        } else if (input[i] == '\\' && input[i + 1] == 'r' && input[i + 2] == 'n') {
            found_crlf = 1;
        }
    }

    if (found_crlf) {
        printf("windows\n");
    } else if (found_cr) {
        printf("mac\n");
    } else if (found_lf) {
        printf("linux\n");
    }

    return 0;
}