#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[1001];
    scanf("%s", input);
    int length = strlen(input);
    int position = 0;
    int distance = 0;

    for (int i = 0; i < length; i++) {
        if (input[i] == 'F') {
            i++;
            int num = 0;
            while (i < length && input[i] >= '0' && input[i] <= '9') {
                num = num * 10 + (input[i] - '0');
                i++;
            }
            i--;
            position += num;
            distance = abs(position);
        } else if (input[i] == 'B') {
            i++;
            int num = 0;
            while (i < length && input[i] >= '0' && input[i] <= '9') {
                num = num * 10 + (input[i] - '0');
                i++;
            }
            i--;
            position -= num;
            distance = abs(position);
        } else if (input[i] == 'R') {
            i += 6; // skip "EPEAT "
            int num = 0;
            while (i < length && input[i] >= '0' && input[i] <= '9') {
                num = num * 10 + (input[i] - '0');
                i++;
            }
            i++;
            int start = i;
            int repeat = 0;
            while (i < length && input[i] != ']') {
                i++;
            }
            char repeat_command[1001];
            strncpy(repeat_command, input + start, i - start);
            repeat_command[i - start] = '\0';
            for (int j = 0; j < num; j++) {
                int temp_position = position;
                int temp_distance = distance;
                sscanf(repeat_command, "%d", &repeat);
                position = temp_position;
                distance = temp_distance;
                for (int k = 0; k < repeat; k++) {
                    for (int l = 0; l < strlen(repeat_command); l++) {
                        if (repeat_command[l] == 'F') {
                            l++;
                            int num = 0;
                            while (l < strlen(repeat_command) && repeat_command[l] >= '0' && repeat_command[l] <= '9') {
                                num = num * 10 + (repeat_command[l] - '0');
                                l++;
                            }
                            l--;
                            position += num;
                            distance = abs(position);
                        } else if (repeat_command[l] == 'B') {
                            l++;
                            int num = 0;
                            while (l < strlen(repeat_command) && repeat_command[l] >= '0' && repeat_command[l] <= '9') {
                                num = num * 10 + (repeat_command[l] - '0');
                                l++;
                            }
                            l--;
                            position -= num;
                            distance = abs(position);
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", distance);
    return 0;
}