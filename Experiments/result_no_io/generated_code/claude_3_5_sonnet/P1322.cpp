#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse_command(char **cmd) {
    int distance = 0;
    if (strncmp(*cmd, "FD ", 3) == 0) {
        distance = atoi(*cmd + 3);
        *cmd += strcspn(*cmd, " ") + 1;
    } else if (strncmp(*cmd, "BK ", 3) == 0) {
        distance = -atoi(*cmd + 3);
        *cmd += strcspn(*cmd, " ") + 1;
    } else if (strncmp(*cmd, "REPEAT ", 7) == 0) {
        int repeat = atoi(*cmd + 7);
        *cmd = strchr(*cmd, '[') + 1;
        char *end = strchr(*cmd, ']');
        *end = '\0';
        for (int i = 0; i < repeat; i++) {
            char *temp = *cmd;
            while (*temp) {
                distance += parse_command(&temp);
            }
            temp = *cmd;
        }
        *cmd = end + 1;
    }
    return distance;
}

int main() {
    char command[1000];
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0;

    char *cmd = command;
    int total_distance = 0;
    while (*cmd) {
        total_distance += parse_command(&cmd);
    }

    printf("%d\n", abs(total_distance));
    return 0;
}