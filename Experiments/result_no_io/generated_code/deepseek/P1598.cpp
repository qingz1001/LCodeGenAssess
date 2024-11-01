#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100
#define NUM_LINES 4
#define NUM_LETTERS 26

int main() {
    char lines[NUM_LINES][MAX_LINE_LENGTH + 1];
    int count[NUM_LETTERS] = {0};
    int max_count = 0;

    // Read input
    for (int i = 0; i < NUM_LINES; i++) {
        fgets(lines[i], MAX_LINE_LENGTH + 1, stdin);
        for (int j = 0; lines[i][j] != '\0' && lines[i][j] != '\n'; j++) {
            if (isupper(lines[i][j])) {
                count[lines[i][j] - 'A']++;
                if (count[lines[i][j] - 'A'] > max_count) {
                    max_count = count[lines[i][j] - 'A'];
                }
            }
        }
    }

    // Print the histogram
    for (int i = max_count; i > 0; i--) {
        for (int j = 0; j < NUM_LETTERS; j++) {
            if (count[j] >= i) {
                printf("*");
            } else {
                printf(" ");
            }
            if (j < NUM_LETTERS - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    // Print the letters
    for (int j = 0; j < NUM_LETTERS; j++) {
        printf("%c", 'A' + j);
        if (j < NUM_LETTERS - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}