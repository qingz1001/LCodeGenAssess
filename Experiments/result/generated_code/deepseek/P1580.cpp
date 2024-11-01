#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1001
#define MAX_LINES 50001

int main() {
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int n = 0;
    char target[MAX_LINE_LENGTH];
    char first_speaker[MAX_LINE_LENGTH];
    int successful = 1;
    int break_line = -1;
    char break_speaker[MAX_LINE_LENGTH];

    // Read input
    while (fgets(lines[n], MAX_LINE_LENGTH, stdin) != NULL) {
        if (lines[n][0] == '\n') break; // End of input
        n++;
    }

    // Extract the target and first speaker
    char *colon = strchr(lines[0], ':');
    if (colon) {
        *colon = '\0';
        strcpy(first_speaker, lines[0]);
        strcpy(target, colon + 2);
        target[strcspn(target, " ")] = '\0'; // Remove everything after the first space
    }

    // Check the queue shape
    for (int i = 1; i < n; i++) {
        colon = strchr(lines[i], ':');
        if (colon) {
            *colon = '\0';
            char *at_pos = strchr(colon + 2, '@');
            if (at_pos) {
                char *at_target = at_pos + 1;
                at_target[strcspn(at_target, " ")] = '\0'; // Remove everything after the first space
                if (strcmp(at_target, target) != 0) {
                    successful = 0;
                    break_line = i + 1;
                    strcpy(break_speaker, lines[i]);
                    break;
                }
            } else {
                successful = 0;
                break_line = i + 1;
                strcpy(break_speaker, lines[i]);
                break;
            }
        }
    }

    // Output result
    if (successful) {
        printf("Successful @%s attempt\n", target);
    } else {
        printf("Unsuccessful @%s attempt\n", target);
        printf("%d\n", break_line);
        printf("%s\n", break_speaker);
    }

    return 0;
}