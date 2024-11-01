#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1001
#define MAX_LINES 50000

int main() {
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int n = 0;
    char first_at[MAX_LINE_LENGTH];
    int first_at_set = 0;
    int successful_attempt = 1;
    int break_line = -1;
    char break_id[MAX_LINE_LENGTH];

    while (fgets(lines[n], MAX_LINE_LENGTH, stdin) != NULL) {
        if (lines[n][0] == '\n') break; // End of input
        n++;
    }

    for (int i = 0; i < n; i++) {
        char *colon = strchr(lines[i], ':');
        if (colon == NULL) continue;

        char *at = strchr(colon, '@');
        if (at == NULL) {
            successful_attempt = 0;
            break_line = i + 1;
            strncpy(break_id, lines[i], colon - lines[i]);
            break_id[colon - lines[i]] = '\0';
            break;
        }

        if (!first_at_set) {
            strcpy(first_at, at);
            first_at_set = 1;
        } else {
            if (strcmp(first_at, at) != 0) {
                successful_attempt = 0;
                break_line = i + 1;
                strncpy(break_id, lines[i], colon - lines[i]);
                break_id[colon - lines[i]] = '\0';
                break;
            }
        }
    }

    if (successful_attempt) {
        printf("Successful @%s attempt\n", first_at + 1);
    } else {
        printf("Unsuccessful @%s attempt\n", first_at + 1);
        printf("%d\n", break_line);
        printf("%s\n", break_id);
    }

    if (successful_attempt && break_line == -1) {
        printf("Unsuccessful @%s attempt\n", first_at + 1);
        printf("%d\n", n);
        printf("Good Queue Shape\n");
    }

    return 0;
}