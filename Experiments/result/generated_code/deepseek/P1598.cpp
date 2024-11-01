#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100
#define NUM_LINES 4

int main() {
    char lines[NUM_LINES][MAX_LINE_LENGTH + 1];
    int count[26] = {0};
    int max_count = 0;

    // Read input
    for (int i = 0; i < NUM_LINES; i++) {
        fgets(lines[i], MAX_LINE_LENGTH + 1, stdin);
        for (int j = 0; lines[i][j] != '\0'; j++) {
            if (isupper(lines[i][j])) {
                count[lines[i][j] - 'A']++;
                if (count[lines[i][j] - 'A'] > max_count) {
                    max_count = count[lines[i][j] - 'A'];
                }
            }
        }
    }

    // Print histogram
    for (int i = max_count; i > 0; i--) {
        for (int j = 0; j < 26; j++) {
            if (count[j] >= i) {
                printf("*");
            } else {
                printf(" ");
            }
            if (j < 25) {
                printf(" ");
            }
        }
        printf("\n");
    }

    // Print alphabet line
    for (int i = 0; i < 26; i++) {
        printf("%c", 'A' + i);
        if (i < 25) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}