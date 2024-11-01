#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 101
#define NUM_CHARS 26

int main() {
    char lines[4][MAX_LINE_LENGTH];
    int count[NUM_CHARS] = {0};
    int max_count = 0;

    // Read input lines
    for (int i = 0; i < 4; i++) {
        fgets(lines[i], MAX_LINE_LENGTH, stdin);
        for (int j = 0; lines[i][j] != '\0'; j++) {
            if (lines[i][j] >= 'A' && lines[i][j] <= 'Z') {
                count[lines[i][j] - 'A']++;
                if (count[lines[i][j] - 'A'] > max_count) {
                    max_count = count[lines[i][j] - 'A'];
                }
            }
        }
    }

    // Print histogram
    for (int i = max_count; i > 0; i--) {
        for (int j = 0; j < NUM_CHARS; j++) {
            if (count[j] >= i) {
                printf("*");
            } else {
                printf(" ");
            }
            if (j < NUM_CHARS - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    // Print alphabet
    for (int i = 0; i < NUM_CHARS; i++) {
        printf("%c", 'A' + i);
        if (i < NUM_CHARS - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}