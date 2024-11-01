#include <stdio.h>
#include <string.h>

int main() {
    char input[100001];
    fgets(input, sizeof(input), stdin);
    
    int len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
        len--;
    }

    int hasR = 0, hasN = 0;
    for (int i = 0; i < len - 1; i++) {
        if (input[i] == '\\') {
            if (input[i+1] == 'r') {
                hasR = 1;
            } else if (input[i+1] == 'n') {
                hasN = 1;
            }
        }
    }

    if (hasR && hasN) {
        printf("windows\n");
    } else if (hasN) {
        printf("linux\n");
    } else if (hasR) {
        printf("mac\n");
    }

    return 0;
}