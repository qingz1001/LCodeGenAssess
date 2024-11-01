#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse_command(char *cmd, int *index);

int main() {
    char command[1000];
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0;  // 移除换行符

    int index = 0;
    int distance = parse_command(command, &index);
    printf("%d\n", abs(distance));

    return 0;
}

int parse_command(char *cmd, int *index) {
    int distance = 0;
    char instruction[10];
    int value;

    while (sscanf(cmd + *index, "%s%n", instruction, &value) == 1) {
        *index += value;

        if (strcmp(instruction, "FD") == 0) {
            sscanf(cmd + *index, "%d%n", &value, &value);
            *index += value;
            distance += value;
        } else if (strcmp(instruction, "BK") == 0) {
            sscanf(cmd + *index, "%d%n", &value, &value);
            *index += value;
            distance -= value;
        } else if (strcmp(instruction, "REPEAT") == 0) {
            int repeat_count;
            sscanf(cmd + *index, "%d%n", &repeat_count, &value);
            *index += value;

            // 跳过左方括号
            *index += 1;

            int sub_distance = parse_command(cmd, index);

            // 跳过右方括号
            *index += 1;

            distance += repeat_count * sub_distance;
        } else if (instruction[0] == ']') {
            break;
        }
    }

    return distance;
}