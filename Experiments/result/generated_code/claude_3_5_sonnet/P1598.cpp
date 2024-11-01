#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100
#define ALPHABET_SIZE 26

int main() {
    char line[MAX_LENGTH + 1];
    int count[ALPHABET_SIZE] = {0};
    int max_count = 0;

    for (int i = 0; i < 4; i++) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        for (int j = 0; line[j] != '\0'; j++) {
            if (isupper(line[j])) {
                count[line[j] - 'A']++;
                if (count[line[j] - 'A'] > max_count) {
                    max_count = count[line[j] - 'A'];
                }
            }
        }
    }

    for (int i = max_count; i > 0; i--) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (count[j] >= i) {
                printf("*");
            } else {
                printf(" ");
            }
            if (j < ALPHABET_SIZE - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c", 'A' + i);
        if (i < ALPHABET_SIZE - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}