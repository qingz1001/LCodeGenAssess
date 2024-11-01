#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 26
#define MAX_LINES 2501

int main() {
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int line_count = 0;

    while (fgets(lines[line_count], MAX_LINE_LENGTH, stdin) != NULL && strcmp(lines[line_count], "E\n") != 0) {
        line_count++;
    }

    for (int i = 0; i < line_count; i++) {
        int score11[2] = {0, 0};
        int score21[2] = {0, 0};
        int len = strlen(lines[i]) - 1; // Remove newline character

        for (int j = 0; j < len; j++) {
            if (lines[i][j] == 'W') {
                score11[0]++;
                score21[0]++;
            } else if (lines[i][j] == 'L') {
                score11[1]++;
                score21[1]++;
            }

            if ((score11[0] >= 11 || score11[1] >= 11) && abs(score11[0] - score11[1]) >= 2) {
                printf("%d:%d\n", score11[0], score11[1]);
                score11[0] = 0;
                score11[1] = 0;
            }

            if ((score21[0] >= 21 || score21[1] >= 21) && abs(score21[0] - score21[1]) >= 2) {
                printf("%d:%d\n", score21[0], score21[1]);
                score21[0] = 0;
                score21[1] = 0;
            }
        }

        if (i < line_count - 1) {
            printf("\n");
        }
    }

    return 0;
}