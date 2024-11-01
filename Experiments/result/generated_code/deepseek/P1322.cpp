#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000

int parse_command(char *command, int *pos);

int main() {
    char command[MAX_LEN];
    fgets(command, MAX_LEN, stdin);
    command[strcspn(command, "\n")] = 0; // Remove newline character

    int pos = 0;
    parse_command(command, &pos);

    printf("%d\n", abs(pos));
    return 0;
}

int parse_command(char *command, int *pos) {
    char *token = strtok(command, " ");
    while (token != NULL) {
        if (strcmp(token, "FD") == 0) {
            token = strtok(NULL, " ");
            *pos += atoi(token);
        } else if (strcmp(token, "BK") == 0) {
            token = strtok(NULL, " ");
            *pos -= atoi(token);
        } else if (strcmp(token, "REPEAT") == 0) {
            token = strtok(NULL, "[");
            int repeat_count = atoi(token);
            char repeat_command[MAX_LEN];
            strcpy(repeat_command, strtok(NULL, "]"));
            for (int i = 0; i < repeat_count; i++) {
                parse_command(repeat_command, pos);
            }
        }
        token = strtok(NULL, " ");
    }
    return *pos;
}