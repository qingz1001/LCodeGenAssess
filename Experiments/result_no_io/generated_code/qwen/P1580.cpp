#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1001
#define MAX_NAME_LENGTH 20

typedef struct {
    char name[MAX_NAME_LENGTH];
    int line_number;
} Person;

int main() {
    char line[MAX_LINE_LENGTH];
    Person current_person = {0};
    int queue_length = 0;
    int first_break_line = -1;
    char first_break_name[MAX_NAME_LENGTH] = {0};

    while (fgets(line, sizeof(line), stdin) != NULL && strcmp(line, "\n") != 0) {
        if (queue_length == 0) {
            sscanf(line, "%[^:]:", current_person.name);
            queue_length++;
        } else {
            char temp_name[MAX_NAME_LENGTH];
            if (sscanf(line, "@%[^:]", temp_name) == 1) {
                if (strcmp(temp_name, current_person.name) != 0) {
                    if (first_break_line == -1) {
                        first_break_line = queue_length;
                        strcpy(first_break_name, temp_name);
                    }
                } else {
                    first_break_line = -1;
                }
            }
            queue_length++;
        }
    }

    if (first_break_line != -1) {
        printf("Unsuccessful @%s attempt\n", first_break_name);
        printf("%d\n", first_break_line);
        printf("%s\n", first_break_name);
    } else {
        printf("Unsuccessful @%s attempt\n", current_person.name);
        printf("%d\n", queue_length);
        printf("Good Queue Shape\n");
    }

    return 0;
}