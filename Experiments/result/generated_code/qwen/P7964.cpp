#include <stdio.h>
#include <string.h>

#define MAX_COMMANDS 100
#define MAX_TITLE_LENGTH 20

typedef struct {
    char title[MAX_TITLE_LENGTH + 1];
    int level;
} Command;

int main() {
    int n;
    scanf("%d", &n);
    Command commands[MAX_COMMANDS];

    for (int i = 0; i < n; i++) {
        scanf("%s %s", commands[i].title, commands[i].title);
        if (strcmp(commands[i].title, "section") == 0) {
            commands[i].level = 1;
        } else if (strcmp(commands[i].title, "subsection") == 0) {
            commands[i].level = 2;
        } else if (strcmp(commands[i].title, "subsubsection") == 0) {
            commands[i].level = 3;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= commands[i].level - 1; j++) {
            printf(".");
        }
        printf("%d %s\n", i + 1, commands[i].title);
    }

    return 0;
}