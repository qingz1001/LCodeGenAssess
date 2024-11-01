#include <stdio.h>
#include <string.h>

#define MAX_COMMANDS 100
#define MAX_TITLE_LENGTH 21

typedef struct {
    int level;
    char title[MAX_TITLE_LENGTH];
} Title;

int main() {
    int n;
    scanf("%d", &n);
    Title titles[MAX_COMMANDS];
    int current_level = 0;
    int max_level = 0;

    for (int i = 0; i < n; i++) {
        char command[20];
        scanf("%s %s", command, titles[i].title);

        if (strcmp(command, "section") == 0) {
            titles[i].level = ++current_level;
            max_level = current_level;
        } else if (strcmp(command, "subsection") == 0) {
            titles[i].level = ++current_level;
            if (current_level > max_level) {
                max_level = current_level;
            }
        } else if (strcmp(command, "subsubsection") == 0) {
            titles[i].level = ++current_level;
            if (current_level > max_level) {
                max_level = current_level;
            }
        }

        current_level--;
    }

    for (int i = 0; i < n; i++) {
        printf("%*s%s\n", titles[i].level * 2, "", titles[i].title);
    }

    return 0;
}