#include <stdio.h>
#include <string.h>

#define MAX_LINE 1000

int main() {
    char line[MAX_LINE], first_person[MAX_LINE], target[MAX_LINE];
    int queue_shape = 0, first_break = 0;
    char breaker[MAX_LINE] = "";

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%[^:]: @%s", first_person, target);

    while (1) {
        if (!fgets(line, sizeof(line), stdin) || line[0] == '\n') {
            break;
        }

        queue_shape++;
        char sender[MAX_LINE], content[MAX_LINE];
        sscanf(line, "%[^:]: %[^\n]", sender, content);

        char *at = strchr(content, '@');
        if (at != NULL) {
            char mentioned[MAX_LINE];
            sscanf(at + 1, "%s", mentioned);
            
            if (strcmp(mentioned, target) != 0 || strchr(at + 1, '@') != NULL) {
                if (!first_break) {
                    first_break = queue_shape;
                    strcpy(breaker, sender);
                }
            }
        } else {
            if (!first_break) {
                first_break = queue_shape;
                strcpy(breaker, sender);
            }
        }

        if (strcmp(sender, target) == 0) {
            printf("Successful @%s attempt\n", target);
            return 0;
        }
    }

    printf("Unsuccessful @%s attempt\n", target);
    if (first_break) {
        printf("%d\n%s\n", first_break, breaker);
    } else {
        printf("%d\nGood Queue Shape\n", queue_shape);
    }

    return 0;
}