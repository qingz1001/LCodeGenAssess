#include <stdio.h>
#include <string.h>

int main() {
    char command[1000];
    int distance = 0;
    int i, j, num;

    scanf("%s", command);

    for (i = 0; i < strlen(command);) {
        if (command[i] == 'F') {
            sscanf(&command[i], "FD %d", &num);
            distance += num;
            i += 3 + snprintf(NULL, 0, "%d", num);
        } else if (command[i] == 'B') {
            sscanf(&command[i], "BK %d", &num);
            distance -= num;
            i += 3 + snprintf(NULL, 0, "%d", num);
        } else if (command[i] == 'R') {
            i++;
            while (command[i] != '[') i++;
            i++;
            int repeat_count = 0;
            int start = i;
            while (command[i] != ']') {
                if (command[i] == 'F' || command[i] == 'B') {
                    i += 3 + snprintf(NULL, 0, "%d", num);
                }
                i++;
            }
            repeat_count = command[start - 1] - '0';
            int sub_distance = 0;
            for (j = 0; j < repeat_count; j++) {
                sub_distance += distance;
            }
            distance = sub_distance;
        }
    }

    printf("%d\n", abs(distance));

    return 0;
}