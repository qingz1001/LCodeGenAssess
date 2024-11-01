#include <stdio.h>
#include <string.h>

#define MAX_CHARS 100

int main() {
    char line[MAX_CHARS + 1];
    int count[26] = {0};
    int max_count = 0;

    // Read input and count occurrences
    for (int i = 0; i < 4; i++) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        for (int j = 0; line[j] != '\0' && line[j] != '\n'; j++) {
            if (line[j] >= 'A' && line[j] <= 'Z') {
                count[line[j] - 'A']++;
                if (count[line[j] - 'A'] > max_count) {
                    max_count = count[line[j] - 'A'];
                }
            }
        }
    }

    // Print vertical histogram
    for (int i = max_count; i > 0; i--) {
        for (int j = 0; j < 26; j++) {
            if (count[j] >= i) {
                printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }

    // Print alphabet
    for (int i = 0; i < 26; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");

    return 0;
}