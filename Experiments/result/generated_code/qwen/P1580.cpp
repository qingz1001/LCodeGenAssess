#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1001
#define NUM_PEOPLE 4

char people[NUM_PEOPLE][MAX_LINE_LENGTH] = {
    "yyy loves OI",
    "yyy loves Maths",
    "yyy loves Chemistry",
    "yyy loves Physics"
};

int main() {
    char line[MAX_LINE_LENGTH];
    int first_line = 0;
    int break_line = -1;
    int break_id = -1;

    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '\n') {
            break;
        }

        if (first_line == 0) {
            for (int i = 0; i < NUM_PEOPLE; i++) {
                if (strstr(line, people[i])) {
                    first_line = 1;
                    break;
                }
            }
        } else {
            int found = 0;
            for (int i = 0; i < NUM_PEOPLE; i++) {
                if (strstr(line, people[i]) && i != 3) {
                    if (!found) {
                        found = 1;
                    } else {
                        break_line = first_line;
                        break_id = i;
                        break;
                    }
                }
            }
            if (break_line != -1) {
                break;
            }
        }
        first_line++;
    }

    if (break_line != -1) {
        printf("Unsuccessful @%s attempt\n", people[3]);
        printf("%d\n", break_line);
        printf("%s\n", people[break_id]);
    } else {
        printf("Unsuccessful @%s attempt\n", people[3]);
        printf("%d\n", first_line);
        printf("Good Queue Shape\n");
    }

    return 0;
}