#include <stdio.h>
#include <string.h>

int main() {
    char input[100001];
    fgets(input, sizeof(input), stdin);
    
    int len = strlen(input);
    int has_r = 0, has_n = 0;
    
    for (int i = 0; i < len - 1; i++) {
        if (input[i] == '\\') {
            if (input[i+1] == 'r') {
                has_r = 1;
            } else if (input[i+1] == 'n') {
                has_n = 1;
            }
        }
    }
    
    if (has_r && has_n) {
        printf("windows\n");
    } else if (has_n) {
        printf("linux\n");
    } else if (has_r) {
        printf("mac\n");
    }
    
    return 0;
}