#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main() {
    char line[MAX_LINE_LENGTH];
    char first_person[MAX_LINE_LENGTH], first_person_id[MAX_LINE_LENGTH];
    char current_person[MAX_LINE_LENGTH], current_person_id[MAX_LINE_LENGTH];
    int line_number = 0, broken_line = 0;
    int queue_length = 0;
    int queue_shape_good = 1;

    // Read the first line
    fgets(line, MAX_LINE_LENGTH, stdin);
    if (line[0] == '\n') {
        return 0; // End of file
    }

    // Parse the first line
    sscanf(line, "%[^:]: %s", first_person, current_person);
    sscanf(first_person, "yyy loves %s", first_person_id);
    sscanf(current_person, "@%s", current_person_id);

    queue_length = 1;

    // Process the remaining lines
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        line_number++;
        if (line[0] == '\n') {
            break; // End of file
        }

        sscanf(line, "%[^:]: %s", current_person, current_person_id);

        if (strcmp(current_person_id, first_person_id) != 0) {
            queue_shape_good = 0;
            broken_line = line_number;
            break;
        }

        queue_length++;
    }

    // Output the result
    if (queue_shape_good) {
        printf("Unsuccessful @%s attempt\n", first_person_id);
        printf("%d\n", queue_length);
        printf("Good Queue Shape\n");
    } else {
        printf("Unsuccessful @%s attempt\n", first_person_id);
        printf("%d\n", broken_line);
        printf("Successful @%s attempt\n", current_person_id);
    }

    return 0;
}