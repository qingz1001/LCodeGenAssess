#include <stdio.h>
#include <string.h>

void compress_ipv6(char *input, char *output) {
    int i, j = 0, start = -1, end = -1;
    for (i = 0; i <= 39; i++) {
        if (input[i] == ':') {
            if (start == -1 && end == -1) {
                start = i;
            } else if (end != -1) {
                end = i;
                break;
            }
        }
    }
    if (end != -1) {
        strncpy(output, input, start);
        output[start++] = ':';
        output[start++] = ':';
        strcpy(output + start, input + end + 1);
    } else {
        strcpy(output, input);
    }
}

int main() {
    char input[40], output[40];
    scanf("%s", input);
    compress_ipv6(input, output);
    printf("%s\n", output);
    return 0;
}