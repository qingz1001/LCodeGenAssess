#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define NUM_LETTERS 26

int main() {
    char lines[4][MAX_LINE_LENGTH + 1];
    int count[NUM_LETTERS] = {0};

    for (int i = 0; i < 4; i++) {
        fgets(lines[i], MAX_LINE_LENGTH + 1, stdin);
        for (int j = 0; lines[i][j] != '\0' && lines[i][j] != '\n'; j++) {
            if (lines[i][j] >= 'A' && lines[i][j] <= 'Z') {
                count[lines[i][j] - 'A']++;
            }
        }
    }

    int max_count = 0;
    for (int i = 0; i < NUM_LETTERS; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }

    for (int i = max_count; i > 0; i--) {
        for (int j = 0; j < NUM_LETTERS; j++) {
            if (count[j] >= i) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < NUM_LETTERS; i++) {
        printf("%c", 'A' + i);
    }
    printf("\n");

    return 0;
}