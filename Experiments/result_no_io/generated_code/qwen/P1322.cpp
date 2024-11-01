#include <stdio.h>
#include <string.h>

int main() {
    char command[1000];
    int distance = 0;
    int stack[100], top = -1;

    fgets(command, sizeof(command), stdin);

    for (int i = 0; i < strlen(command); ++i) {
        if (command[i] == 'F' || command[i] == 'B') {
            int step = 0;
            while (isdigit(command[++i])) {
                step = step * 10 + (command[i] - '0');
            }
            if (command[i - 1] == 'F') {
                distance += step;
            } else {
                distance -= step;
            }
        } else if (command[i] == '[') {
            stack[++top] = distance;
        } else if (command[i] == ']') {
            distance = stack[top--];
        }
    }

    printf("%d\n", distance);
    return 0;
}