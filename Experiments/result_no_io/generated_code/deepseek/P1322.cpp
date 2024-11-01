#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1000

int parse_number(char *str, int *index) {
    int number = 0;
    while (str[*index] >= '0' && str[*index] <= '9') {
        number = number * 10 + (str[*index] - '0');
        (*index)++;
    }
    return number;
}

int process_command(char *command) {
    int distance = 0;
    int i = 0;

    while (command[i] != '\0') {
        if (command[i] == 'F' && command[i + 1] == 'D') {
            i += 3; // Skip "FD "
            int steps = parse_number(command, &i);
            distance += steps;
        } else if (command[i] == 'B' && command[i + 1] == 'K') {
            i += 3; // Skip "BK "
            int steps = parse_number(command, &i);
            distance -= steps;
        } else if (command[i] == 'R' && command[i + 1] == 'E' && command[i + 2] == 'P' && command[i + 3] == 'E' && command[i + 4] == 'A' && command[i + 5] == 'T') {
            i += 7; // Skip "REPEAT "
            int repeat_count = parse_number(command, &i);
            i++; // Skip '['
            int start_repeat = i;
            int repeat_depth = 1;
            while (repeat_depth > 0) {
                if (command[i] == '[') repeat_depth++;
                if (command[i] == ']') repeat_depth--;
                i++;
            }
            char sub_command[MAX_COMMAND_LENGTH];
            strncpy(sub_command, command + start_repeat, i - start_repeat - 1);
            sub_command[i - start_repeat - 1] = '\0';
            int sub_distance = process_command(sub_command);
            distance += repeat_count * sub_distance;
        } else {
            i++;
        }
    }

    return distance;
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    // Remove newline character if present
    command[strcspn(command, "\n")] = '\0';

    int result = process_command(command);
    printf("%d\n", abs(result));

    return 0;
}