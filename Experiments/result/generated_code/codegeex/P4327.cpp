#include <stdio.h>
#include <string.h>

int main() {
    char s[16];
    scanf("%s", s);
    int len = strlen(s);
    
    // Print the top line of the frames
    for (int i = 0; i < len; i++) {
        printf("..#");
        if ((i + 1) % 3 == 0) {
            printf("*");
        }
    }
    printf("*..\n");
    
    // Print the second line of the frames
    for (int i = 0; i < len; i++) {
        printf(".#.");
        if ((i + 1) % 3 == 0) {
            printf(".*");
        }
    }
    printf(".*.\n");
    
    // Print the third line of the frames
    for (int i = 0; i < len; i++) {
        printf("#.%c", s[i]);
        if ((i + 1) % 3 == 0) {
            printf(".X");
        } else {
            printf(".");
        }
    }
    printf(".\n");
    
    // Print the fourth line of the frames
    for (int i = 0; i < len; i++) {
        printf(".#.");
        if ((i + 1) % 3 == 0) {
            printf(".*");
        }
    }
    printf(".*.\n");
    
    // Print the bottom line of the frames
    for (int i = 0; i < len; i++) {
        printf("..#");
        if ((i + 1) % 3 == 0) {
            printf("*");
        }
    }
    printf("*..\n");
    
    return 0;
}